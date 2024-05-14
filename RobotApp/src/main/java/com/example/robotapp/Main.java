package com.example.robotapp;

import javafx.application.Application;
import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

import javax.bluetooth.BluetoothStateException;
import javax.bluetooth.LocalDevice;
import java.awt.event.ActionEvent;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.PrintWriter;

public class Main extends Application {

    SPPClient client;

    String myName;
    String partnerName;

    BufferedReader in;
    PrintWriter out;

    ScreensController mainContainer;

    public Main() {
        mainContainer = new ScreensController(this);
        mainContainer.loadScreen("ChatScreen", "ChatScreen.fxml");
        mainContainer.loadScreen("LoadingScreen", "LoadingScreen.fxml");
        mainContainer.loadScreen("ServerListScreen", "ServerListScreen.fxml");
        mainContainer.loadScreen("ControlUi", "ControlUi.fxml");
        mainContainer.setScreen("LoadingScreen.fxml");

        try {
            LocalDevice localDevice = LocalDevice.getLocalDevice();
            myName = localDevice.getFriendlyName();
        } catch (BluetoothStateException e) {
            e.fillInStackTrace();
        }
        initClient();
    }

    public void initClient() {
        client = new SPPClient();
        client.setOnDeviceDiscovery((ActionEvent e) -> {
            ObservableList<RemoteDeviceInfo> devInfo = FXCollections.observableList(client.getDeviceInfos());
            ((ServerListScreenController) mainContainer.getScreenController("ServerListScreen")).setTableData(devInfo);
            mainContainer.setScreen("ServerListScreen");
        });
        ((LoadingScreenController) mainContainer.getScreenController("LoadingScreen")).setText("Searching for Bluetooth Devices ...");
        mainContainer.setScreen("LoadingScreen");
        client.startDiscovery();

        client.setOnConnectionFailed((ActionEvent e) -> mainContainer.setScreen("ServerListScreen"));
        client.setOnConnectionSuccessful((ActionEvent e) -> {
            in = client.in;
            out = client.out;
            partnerName = client.partnerName;
            mainContainer.setScreen("ControlUi");
            (new streamPoller()).start();
        });
    }

    public void refresh() {
        ((LoadingScreenController) mainContainer.getScreenController("LoadingScreen")).setText("Searching for Bluetooth Devices ...");
        mainContainer.setScreen("LoadingScreen");
        client.startDiscovery();
    }


    public void connectToDevice(int index) {
        ((LoadingScreenController) mainContainer.getScreenController("LoadingScreen")).setText("Connecting ...");
        mainContainer.setScreen("LoadingScreen");
        client.connect(index);
    }

    public void reconnectDevice() {
        client.reconnect();
    }

    public void sendMsg(String s) {
        System.out.println("must send " + s);
        out.write(s);
        out.flush();
    }

    public void receiveMsg(String s) {
        ChatScreenController ch = ((ChatScreenController) mainContainer.getScreenController("ChatScreen"));
        ch.receivedMassage(s);
        ControlUiController cu = ((ControlUiController) mainContainer.getScreenController("ControlUi"));
        cu.receivedMassage(s);
    }

    class streamPoller extends Thread {

        public void run() {
            boolean isRun = true;
            while (isRun) {
                try {
                    if (in != null) {
                        System.out.println("in not null");
                        String s = in.readLine();
                        if (s != null) Platform.runLater(() -> receiveMsg(s));
                        else isRun = false;
                    }
                } catch (IOException e) {
                    e.fillInStackTrace();
                }
            }
        }
    }

    @Override
    public void start(Stage primaryStage) throws Exception {
        AnchorPane root = new AnchorPane();
        root.getChildren().addAll(mainContainer);
        AnchorPane.setTopAnchor(mainContainer, 0.0);
        AnchorPane.setBottomAnchor(mainContainer, 0.0);
        AnchorPane.setLeftAnchor(mainContainer, 0.0);
        AnchorPane.setRightAnchor(mainContainer, 0.0);

        Scene scene = new Scene(root, 800, 700);
        primaryStage.setTitle("AVG");
        primaryStage.getIcons().add(new Image(String.valueOf(getClass().getResource("icon.jpeg"))));
        primaryStage.setScene(scene);
        primaryStage.show();
    }


    public static void main(String[] args) {
        launch(args);
    }
}
