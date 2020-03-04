import java.io.*;
import java.net.*;

class ServerSocket{
  
  public static void main(String argv[]) throws Exception{
    String clientMessage;
    String sentMessage;
  
    ServerSocket welcomeSocket = new ServerSocket(8888); // Tạo socket mở port 8888 để truyền ra ngoài

    while(true){
      Socket connectionSocket = welcomeSocket.accept();// Chấp nhận kết nối incomming connection từ Client 
      
      BufferedReader inFromClient = new BufferedReader(new InputStreamReader(connectionSocket.getInputStream()));// Tạo luồng nhận về
      DataOutputStream outToClient = new DataOutputStream(connectionSocket.getOutputStream());// tạo luồng gửi đi
      
      clientSentence = inFromClient.readLine();
      
      System.out.println("Received: " + clientMessage);// tin gốc nhận từ Client 
      sentMessage = clientMessage.toUpperCase() + '\n';// thay đổi cho uppercase
      outToClient.writeBytes(capitalizedSentence);// gửi lại cho cl
    }
    
  }
  
} 
