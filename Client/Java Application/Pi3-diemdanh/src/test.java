
import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;

import javax.net.ssl.HttpsURLConnection;
import static org.apache.http.HttpHeaders.USER_AGENT;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author trana
 */
public class test {

    public static void main(String args[]) throws org.json.simple.parser.ParseException, MalformedURLException, IOException {
//        JSONParser parser = new JSONParser();
//        Object obj = parser.parse("{ \"array\":[[\"msg 1\",\"msg 2\",\"msg 3\"],[\"msg 4\",\"msg 5\",\"msg 6\"], [\"msss\"]] }");
//        JSONObject jsonObject = (JSONObject) obj;
//        JSONArray msg = (JSONArray) jsonObject.get("array");
//        Iterator<JSONArray> iterator = msg.iterator();
//        
//        module.table.Event e = new module.table.Event();
//        
//        try {
//            System.out.println(e.getData());
//        } catch (SQLException ex) {
//            Logger.getLogger(test.class.getName()).log(Level.SEVERE, null, ex);
//        }
//        
//        while (iterator.hasNext()) {
//            System.out.println(iterator.next().toJSONString());
//        }
//
//        String url = "http://192.168.1.2/nckh/api/gets/organizations";
////        url = "http://sam.doantn.hcmus.edu.vn/api/organizations/";
//
//        CloseableHttpClient httpclient = HttpClients.createDefault();
//        HttpGet httpget = new HttpGet(url);
//        System.out.println("Executing request " + httpget.getRequestLine());
//
//        // Create a custom response handler
//        ResponseHandler<String> responseHandler = response -> {
//            int status = response.getStatusLine().getStatusCode();
//            if (status >= 200 && status < 300) {
//                HttpEntity entity = response.getEntity();
//                return entity != null ? EntityUtils.toString(entity) : null;
//            } else {
//                throw new ClientProtocolException("Unexpected response status: " + status);
//            }
//        };
//        String responseBody = httpclient.execute(httpget, responseHandler);
//        System.out.println("----------------------------------------");
//        //System.out.println(responseBody);
//        
//        Object obj3 = parser.parse(responseBody);
//        JSONArray row = (JSONArray) obj3;
//        //System.out.println(row.toJSONString());
//        
//        Iterator<JSONObject> iterator2 = row.iterator();
//        while (iterator2.hasNext()) {         
//            System.out.println(iterator2.next().toJSONString());
//        }
//        
        String str = "https%3A%2F%2Fmywebsite%2Fdocs%2Fenglish%2Fsite%2Fmybook.do%3Frequest_type";
        System.out.println(java.net.URLDecoder.decode(str, "UTF-8"));
//        System.out.println(java.net.URLEncoder.encode(url, "UTF-8"));

                String url = "http://localhost/getEvent.php";
		URL obj = new URL(url);
		HttpURLConnection con = (HttpURLConnection) obj.openConnection();

		//add reuqest header
		con.setRequestMethod("POST");
		con.setRequestProperty("User-Agent", USER_AGENT);
		con.setRequestProperty("Accept-Language", "en-US,en;q=0.5");

		String urlParameters = "key=b091f0444231106d8e7b796ae7508bb50fc9c17556118fe705266018a4173438";

		// Send post request
		con.setDoOutput(true);
                try (DataOutputStream wr = new DataOutputStream(con.getOutputStream())) {
                    wr.writeBytes(urlParameters);
                    wr.flush();
                }

		int responseCode = con.getResponseCode();
		System.out.println("\nSending 'POST' request to URL : " + url);
		System.out.println("Post parameters : " + urlParameters);
		System.out.println("Response Code : " + responseCode);

		BufferedReader in = new BufferedReader(
		        new InputStreamReader(con.getInputStream()));
		String inputLine;
		StringBuffer response = new StringBuffer();

		while ((inputLine = in.readLine()) != null) {
			response.append(inputLine);
		}
		in.close();

		//print result
		System.out.println(response.toString());
    }

}

