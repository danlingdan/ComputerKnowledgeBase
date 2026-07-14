import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;
import java.nio.charset.StandardCharsets;

public class DateClient {
    private static final int PORT = 6013;

    public static void main(String[] args) {
        try (Socket socket = new Socket("127.0.0.1", PORT);
             BufferedReader input = new BufferedReader(
                     new InputStreamReader(socket.getInputStream(),
                                           StandardCharsets.UTF_8))) {
            String line;
            while ((line = input.readLine()) != null) {
                System.out.println(line);
            }
        } catch (IOException exception) {
            System.err.println("Date client failed: " + exception.getMessage());
        }
    }
}
