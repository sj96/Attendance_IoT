/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package thread;

/**
 *
 * @author trana
 */
public class Get implements Runnable{
    Thread threadAuto;
    private GUI.mainForm mf;
    public Get(Thread threadAuto, GUI.mainForm mf){
        this.threadAuto = threadAuto;
        this.mf = mf;
    }
    
    @Override
    public void run( ){
        threadAuto = new Thread(new AutoSync(mf));
        threadAuto.start();
    }
    public void start () throws InterruptedException
   {
       threadAuto.interrupt();
   }
}
