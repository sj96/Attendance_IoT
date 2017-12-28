/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package module;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Date;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author trana
 */
public class Database {

    private Connection connect = null;

    public Database() throws ClassNotFoundException, SQLException {
        this.connect();
    }

    private void connect() throws ClassNotFoundException , ClassNotFoundException, SQLException {
        
            Class.forName("com.mysql.jdbc.Driver");
            // Setup the connection with the DB
//            String host = "localhost:3307";
            String username = "root";
            String password = "";
            String database = "diemdanh_nckh_webservices";

//            String password = "DiemDanh2017";
            
//            String urlConnect = "jdbc:mysql://127.0.0.1:3307/" + database + "?useUnicode=true&characterEncoding=UTF-8";
            String urlConnect = "jdbc:mysql://127.0.0.1:3306/" + database + "?useUnicode=true&characterEncoding=UTF-8";
            this.connect = DriverManager
                    .getConnection(urlConnect, username, password);
        
    }
    
    public void close(){
        try {
            connect.close();
        } catch (SQLException ex) {
            System.out.println("Conect not close. Error: " + ex.getMessage());
        }
    }
    
    public ResultSet query(String sql){
        try {
            Statement statement;
            statement = this.connect.createStatement();
            return statement.executeQuery(sql);
        } catch (SQLException ex) {
            System.out.println("not query. Error: " + ex.getMessage());
            return null;
        }
    }
    
    public void update(String sql){
        try {
            Statement statement;
            statement = this.connect.createStatement();
            statement.executeUpdate(sql);
        } catch (SQLException ex) {
            System.out.println("not query. Error: " + ex.getMessage());
        }
    }
    
}
