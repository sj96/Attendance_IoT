/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package module.table;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Iterator;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;

/**
 *
 * @author trana
 */
public class table {

    // insert row 
    private boolean insert(int id, String data[]) {
        return true;
    }

    // update row with id
    private boolean update(int id, String data[]) {
        return true;
    }

    // delete row with id
    private boolean delete(int id) {
        return true;
    }

    //get all row in table
    private String getData() {
        try {
            module.Database conn = new module.Database();
            ResultSet resultSet = conn.query(new String());
            String data = null;
            return data;
        } catch (Exception ex) {
            Logger.getLogger(table.class.getName()).log(Level.SEVERE, null, ex);            
            return "";
        } 
    }

    public boolean syncData() {
        String oldData = getData();

        return true;
    }
}
