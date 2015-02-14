/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package quizserver;

import java.io.IOException;
import javax.swing.JOptionPane;

/**
 *
 * @author ritesh
 */
public class QuizServer {
native void initializesocket(int port,String IP);
native int makeConnection();
native String buzzerRound(int fclient,int lclient,int time);
native String passRound(int fclient,int lclient,int currc,int flag,int time);
native void closeAll(int fclient,int lclient);
native void broadcastMessage(String []msg,int fclient,int lclient);
static 
{
        //System.setProperty("java.library.path", "/home/ritesh/NetBeansProjects/CDynamicLibrary/dist/");
        System.load("/home/ritesh/NetBeansProjects/CDynamicLibrary/dist/libctest.so");

}

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws IOException {
        // TODO code application logic here

        String input =  JOptionPane.showInputDialog("Enter No. Of Clients");
        int n = Integer.parseInt(input);
        new connection(n);
    }
    
}
