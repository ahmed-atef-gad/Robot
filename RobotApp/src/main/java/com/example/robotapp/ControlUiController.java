package com.example.robotapp;

import javafx.fxml.FXML;
import javafx.scene.control.ChoiceBox;
import javafx.scene.control.TextArea;
import javafx.scene.effect.Bloom;
import javafx.scene.shape.Circle;

public class ControlUiController implements ControlledScreen {

    ScreensController myScreenController;
    Main myLogicalParent;

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
    TextArea messageArea;

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
    }

    @FXML
    protected void move() {
        String choice = choiceMenu.getValue();
        switch (choice) {
            case "1":
                myLogicalParent.sendMsg("00");
                break;
            case "2":
                myLogicalParent.sendMsg("10");
                break;
            case "3":
                myLogicalParent.sendMsg("20");
                break;
            case "4":
                myLogicalParent.sendMsg("01");
                break;
            case "5":
                myLogicalParent.sendMsg("11");
                break;
            case "6":
                myLogicalParent.sendMsg("21");
                break;
            case "7":
                myLogicalParent.sendMsg("02");
                break;
            case "8":
                myLogicalParent.sendMsg("12");
                break;
            case "9":
                myLogicalParent.sendMsg("22");
                break;
        }
    }

    @FXML
    protected void reconnectDevice() {
        myLogicalParent.reconnectDevice();
        messageArea.clear();
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
        } else {
            messageArea.appendText(msg + "\n");
        }
    }

}
