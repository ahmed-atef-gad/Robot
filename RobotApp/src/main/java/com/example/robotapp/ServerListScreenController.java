package com.example.robotapp;

import javafx.application.Platform;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.TableView;

/**
 * Created by Armin on 7/19/2016.
 */
public class ServerListScreenController implements ControlledScreen {

    ScreensController myScreenController;
    Main myLogicalParent;

    @Override
    public void setParents(ScreensController screenPage, Main logical) {
        myLogicalParent = logical;
        myScreenController = screenPage;
    }

    @FXML
    private TableView<RemoteDeviceInfo> serverTable;

    public void setTableData(ObservableList<RemoteDeviceInfo> data) {
        serverTable.setItems(data);
        for (RemoteDeviceInfo r : data) {
            System.out.println(r.deviceAddress);
            if (r.deviceAddress.toString().equals("StringProperty [value: 201506105306]")) {
                Platform.runLater(() -> myLogicalParent.connectToDevice(data.indexOf(r)));
                break;
            }
        }
    }

    @FXML
    protected void connectToDevice() {
        myLogicalParent.connectToDevice(serverTable.getSelectionModel().getSelectedIndex());
    }

    @FXML
    protected void refresh() {
        myLogicalParent.refresh();
    }

}