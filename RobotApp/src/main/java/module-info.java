module com.example.robotapp {
    requires javafx.controls;
    requires javafx.fxml;
    requires bluecove;
    requires java.desktop;


    opens com.example.robotapp to javafx.fxml;
    exports com.example.robotapp;
}