/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package module.table;

import java.sql.ResultSet;
import java.util.Iterator;
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
    private String[] getData() {
        module.Database conn = new module.Database();
        ResultSet resultSet = conn.query(new String());
        String data[] = null;
        return data;
    }

    public boolean syncData(String data[][]) {
        String[] oldData = getData();
        for (String[] row : data) {

            JSONParser parser = new JSONParser();
            try {
                Object obj = parser.parse("{ \"array\":[\"msg 1\",\"msg 2\",\"msg 3\"] }");

                JSONObject jsonObject = (JSONObject) obj;
                JSONArray msg = (JSONArray) jsonObject.get("array");
                Iterator<JSONArray> iterator = msg.iterator();
                while (iterator.hasNext()) {
                    System.out.println(iterator.next().toJSONString());
                }
            } catch (ParseException e) {
                e.printStackTrace();
            }

        }

        return true;
    }
}
