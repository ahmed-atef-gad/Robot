package com.example.robotapp;

import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.ChoiceBox;
import javafx.scene.control.TextArea;
import javafx.scene.effect.Bloom;
import javafx.scene.input.KeyCode;
import javafx.scene.layout.HBox;
import javafx.scene.shape.Circle;

public class ControlUiController implements ControlledScreen {

    ScreensController myScreenController;
    Main myLogicalParent;
    long time = 0;
    boolean move = true;
    boolean mode = true; //true -> auto | false -> manual
    int nx = 0;
    int ny = 0;

    @FXML
    Circle c1;
    @FXML
    Circle c2;
    @FXML
    Circle c3;
    @FXML
    Circle c4;
    @FXML
    Circle c5;
    @FXML
    Circle c6;
    @FXML
    Circle c7;
    @FXML
    Circle c8;
    @FXML
    Circle c9;

    Circle[][] circles = new Circle[3][3];

    @FXML
    ChoiceBox<String> choiceMenu;
    @FXML
    Button moveButton;

    @FXML
    TextArea messageArea;
    @FXML
    TextArea commandArea;

    @FXML
    HBox mainBox;

    @Override
    public void setParents(ScreensController screenPage, Main logical) {
        myLogicalParent = logical;
        myScreenController = screenPage;
        choiceMenu.getItems().add("1");
        choiceMenu.getItems().add("2");
        choiceMenu.getItems().add("3");
        choiceMenu.getItems().add("4");
        choiceMenu.getItems().add("5");
        choiceMenu.getItems().add("6");
        choiceMenu.getItems().add("7");
        choiceMenu.getItems().add("8");
        choiceMenu.getItems().add("9");
        circles[0][0] = c1;
        circles[0][1] = c2;
        circles[0][2] = c3;
        circles[1][0] = c4;
        circles[1][1] = c5;
        circles[1][2] = c6;
        circles[2][0] = c7;
        circles[2][1] = c8;
        circles[2][2] = c9;

        mainBox.setOnKeyPressed(event -> {
            if (System.currentTimeMillis() - time < 90 && !mode) return;
            time = System.currentTimeMillis();
            if (event.getCode() == KeyCode.W) {
                myLogicalParent.sendMsg("1");
            } else if (event.getCode() == KeyCode.S) {
                myLogicalParent.sendMsg("2");
            } else if (event.getCode() == KeyCode.A) {
                myLogicalParent.sendMsg("3");
            } else if (event.getCode() == KeyCode.D) {
                myLogicalParent.sendMsg("4");
            }
        });
    }

    @FXML
    protected void reset() {
        reset(true);
    }

    void reset(boolean send) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                circles[i][j].setFill(javafx.scene.paint.Color.WHITE);
                circles[i][j].setEffect(null);
            }
        }
        //set active node color #3dea4b
        circles[0][0].setFill(javafx.scene.paint.Color.web("#3dea4b"));
        circles[0][0].setEffect(new Bloom(.3));

        if (send)
            myLogicalParent.sendMsg("-1");

        moveButton.setDisable(false);
    }

    @FXML
    protected void move() {
        String choice = choiceMenu.getValue();
        move = false;
        moveButton.setDisable(true);

        switch (choice) {
            case "1":
                myLogicalParent.sendMsg("00");
                nx = 0;
                ny = 0;
                break;
            case "2":
                myLogicalParent.sendMsg("10");
                nx = 1;
                ny = 0;
                break;
            case "3":
                myLogicalParent.sendMsg("20");
                nx = 2;
                ny = 0;
                break;
            case "4":
                myLogicalParent.sendMsg("01");
                nx = 0;
                ny = 1;
                break;
            case "5":
                myLogicalParent.sendMsg("11");
                nx = 1;
                ny = 1;
                break;
            case "6":
                myLogicalParent.sendMsg("21");
                nx = 2;
                ny = 1;
                break;
            case "7":
                myLogicalParent.sendMsg("02");
                nx = 0;
                ny = 2;
                break;
            case "8":
                myLogicalParent.sendMsg("12");
                nx = 1;
                ny = 2;
                break;
            case "9":
                myLogicalParent.sendMsg("22");
                nx = 2;
                ny = 2;
                break;
        }
    }

    @FXML
    protected void reconnectDevice() {
        myLogicalParent.reconnectDevice();
        messageArea.clear();
    }

    @FXML
    protected void toggleMode() {
        if (mode) {
            mode = false;
            choiceMenu.setDisable(true);
            moveButton.setDisable(true);
            commandArea.setDisable(false);
            myLogicalParent.sendMsg("-100");
        } else {
            mode = true;
            choiceMenu.setDisable(false);
            moveButton.setDisable(false);
            commandArea.setDisable(true);
            myLogicalParent.sendMsg("-");
        }
    }

    public void receivedMassage(String msg) {
        if (msg.startsWith("(")) {
            int x = Integer.parseInt(msg.substring(1, 2));
            int y = Integer.parseInt(msg.substring(3, 4));
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    circles[i][j].setFill(javafx.scene.paint.Color.WHITE);
                    circles[i][j].setEffect(null);
                }
            }
            //set active node color #3dea4b
            circles[y][x].setFill(javafx.scene.paint.Color.web("#3dea4b"));
            circles[y][x].setEffect(new Bloom(.3));
            if (nx == x && ny == y) {
                move = true;
                moveButton.setDisable(false);
            }
        } else if (msg.startsWith("Resetting") || msg.startsWith("Initializing") || msg.startsWith("Calculating gyro")) {
            reset(false);
        } else {
            messageArea.appendText(msg + "\n");
        }
    }

    @FXML
    protected void sendCommand() {
        myLogicalParent.sendMsg(commandArea.getText());
        commandArea.clear();
    }

}
