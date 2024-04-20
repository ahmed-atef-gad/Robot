package com.example.robotapp;

import javafx.fxml.FXML;
import javafx.scene.control.TextArea;
import javafx.scene.text.Text;
import javafx.scene.text.TextFlow;

public class ChatScreenController implements ControlledScreen {

    ScreensController myScreenController;
    Main myLogicalParent;

    @Override
    public void setParents(ScreensController screenPage, Main logical) {
        myLogicalParent = logical;
        myScreenController = screenPage;
    }

    @FXML
    private TextFlow chatLog;

    @FXML
    private TextArea chatText;

    @FXML
    protected void sendMassage() {
        String msg = chatText.getText();
        Text blue = new Text(myLogicalParent.myName + " : ");
        blue.setStyle("-fx-fill: #0098d8");

        Text m = new Text(msg + "\n");

        chatLog.getChildren().add(blue);
        chatLog.getChildren().add(m);

        chatText.setText("");
        myLogicalParent.sendMsg(msg);
    }

    @FXML
    protected void enterPressed(javafx.scene.input.KeyEvent event) {
        if (event.getCode().toString().equals("ENTER")) {
            String msg = chatText.getText();
            Text blue = new Text(myLogicalParent.myName + " : ");
            blue.setStyle("-fx-fill: #0098d8");

            msg = msg.substring(0, msg.length() - 1);

            Text m = new Text(msg + "\n");

            chatLog.getChildren().add(blue);
            chatLog.getChildren().add(m);

            chatText.setText("");
            myLogicalParent.sendMsg(msg);
        }
    }

    @FXML
    protected void reconnectDevice() {
        myLogicalParent.reconnectDevice();
    }

    public void receivedMassage(String msg) {
        Text red = new Text(myLogicalParent.partnerName + " : ");
        red.setStyle("-fx-fill: orangered");

        Text m = new Text(msg + "\n");

        chatLog.getChildren().add(red);
        chatLog.getChildren().add(m);
    }

}
