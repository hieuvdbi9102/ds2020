import java.io.*;
import java.net.*;

class ClientSocket{
  
 public static void main(String argv[]) throws Exception{
  String messageSent;
  String messageReceipt;
   
  BufferedReader userInput = new BufferedReader( new InputStreamReader(System.in)); //Nhập liệu
   
  Socket clientSocket = new Socket("127.0.0.1", 8888); //Tạo socket client là localhost lắng nghe ở cổng 8888 
  DataOutputStream outToServer = new DataOutputStream(clientSocket.getOutputStream()); //tao luồng gửi đi
  BufferedReader inFromServer = new BufferedReader(new InputStreamReader(clientSocket.getInputStream())); // tạo luồng nhận về
   
  messages = userInput.readLine();
  outToServer.writeBytes(messages + '\n'); //gửi đi
   
  messageReceipt = inFromServer.readLine(); //nhận về từ server (text bị chuyển hết thành uppercase ở server để dễ phân biệt )
  System.out.println("FROM SERVER: " + messageReceipt);
   
  clientSocket.close();
 }
  
}
