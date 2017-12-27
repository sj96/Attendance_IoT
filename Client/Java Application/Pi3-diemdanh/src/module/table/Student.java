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
import org.json.simple.parser.ParseException;

/**
 *
 * @author trana
 */
public class Student {

    private module.Database db;

    // insert row 
    private void insert(JSONObject obj) {
        db = new module.Database();
        db.update("INSERT INTO `student`(`id`, `studentID`, `firstNameStudent`, `lastNameStudent`, `idMajor`)"
                + " VALUES (" + obj.get("id") + ",'" + obj.get("studentID") + "','" + obj.get("firstNameStudent") + "','" + obj.get("lastNameStudent") + "','" + obj.get("idMajor") + ")");
    }

    // update row with id
    private void update(String id, JSONObject obj) {
        db = new module.Database();
        db.update("UPDATE `student` SET `studentID`='" + obj.get("studentID") + "',`firstNameStudent`='" + obj.get("firstNameStudent") + "',`lastNameStudent`='" + obj.get("lastNameStudent") + "',`idMajor`='" + obj.get("idMajor") + "' WHERE `id` =" + id);
    }

    // delete row with id
    private void delete(String id) {
        db = new module.Database();
        db.update("DELETE FROM `student` WHERE `id` = " + id);
    }

    //get all row in table
    public String getData() throws SQLException {
        module.Database conn = new module.Database();
        ResultSet resultSet = conn.query("Select * from `student`");
        JSONArray table = new JSONArray();
        while (resultSet.next()) {
            JSONObject row = new JSONObject();
            row.put("id", resultSet.getInt("id"));
            row.put("studentID", resultSet.getString("studentID"));
            row.put("firstNameStudent", resultSet.getString("firstNameStudent"));
            row.put("lastNameStudent", resultSet.getString("lastNameStudent"));
            row.put("idMajor", resultSet.getString("idMajor"));

            table.add(row);
        }
        return table.toJSONString();
    }

    public boolean syncData() throws SQLException, Exception {
        JSONParser parser = new JSONParser();
        String newData = getDataNew();
        Object obj = parser.parse(newData);
        JSONArray New = (JSONArray) obj;

        String oldData = getData();
        parser = new JSONParser();
        Object obj3 = parser.parse(oldData);
        JSONArray old = (JSONArray) obj3;

        Iterator<JSONObject> oldRow = old.iterator();
        Iterator<JSONObject> newRow = New.iterator();
        while (newRow.hasNext()) {
            JSONObject a = newRow.next();
            if (oldRow.hasNext()) {
                JSONObject b = oldRow.next();
                if (Integer.parseInt(a.get("id").toString()) == Integer.parseInt(b.get("id").toString())) {
                    update(a.get("id").toString(), a);
                    System.out.println("1");
                } else if (Integer.parseInt(a.get("id").toString()) > Integer.parseInt(b.get("id").toString())) {
                    delete(b.get("id").toString());
                    System.out.println("2");
                    b = oldRow.next();
                    while (Integer.parseInt(a.get("id").toString()) > Integer.parseInt(b.get("id").toString()) && oldRow.hasNext()) {
                        delete(a.get("id").toString());
                        b = oldRow.next();
                        if (Integer.parseInt(a.get("id").toString()) < Integer.parseInt(b.get("id").toString())) {
                            insert(a);
                        } else if (Integer.parseInt(a.get("id").toString()) == Integer.parseInt(b.get("id").toString())) {
                            update(a.get("id").toString(), a);
                            System.out.println("1");
                        }
                    }
                } else {
                    insert(a);
                    a = newRow.next();
                    System.out.println("3");
                    while (Integer.parseInt(a.get("id").toString()) < Integer.parseInt(b.get("id").toString()) && oldRow.hasNext()) {
                        insert(a);
                        b = oldRow.next();
                        if (Integer.parseInt(a.get("id").toString()) > Integer.parseInt(b.get("id").toString())) {
                            delete(b.get("id").toString());
                            b = oldRow.next();
                        }
                    }
                }
            } else {
                insert(a);
            }

        }
        while (oldRow.hasNext()) {
            JSONObject b = oldRow.next();
            delete(b.get("id").toString());
        }

        return true;
    }

    // HTTP POST request
    private String getDataNew() throws Exception {

        String host = module.Seting.server+"/students";

        module.Get get = new module.Get();

        return get.get(host);
    }
}
