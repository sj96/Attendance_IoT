/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package module.table;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.InputStreamReader;
import java.net.URL;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Iterator;
import javax.net.ssl.HttpsURLConnection;
import static org.apache.http.HttpHeaders.USER_AGENT;
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;

/**
 *
 * @author trana
 */
public class Attendance {
    //get all row in table

    public String getData() throws SQLException {
        module.Database conn = new module.Database();
        ResultSet resultSet = conn.query("Select * from `attendance`");
        JSONArray table = new JSONArray();
        while (resultSet.next()) {
            JSONObject row = new JSONObject();
            row.put("id", resultSet.getInt("id"));
            row.put("idEvent", resultSet.getString("idEvent"));
            row.put("idCard", resultSet.getString("idCard"));
            row.put("timeIn", resultSet.getString("timeIn"));
            row.put("timeOut", resultSet.getString("timeOut"));

            table.add(row);
        }
        return table.toJSONString();
    }

}
