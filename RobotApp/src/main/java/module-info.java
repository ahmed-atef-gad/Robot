module com.example.robotapp {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.desktop;
    requires bluecove;


    opens com.example.robotapp to javafx.fxml;
    exports com.example.robotapp;
}