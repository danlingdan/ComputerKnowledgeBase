import java.io.IOException;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.time.Instant;

public class DateServer {
    private static final int PORT = 6013;

    public static void main(String[] args) {
        try (ServerSocket server = new ServerSocket(PORT)) {
            System.out.printf("Date server listening on port %d%n", PORT);
            while (true) {
                try (Socket client = server.accept();
                     PrintWriter output =
                             new PrintWriter(client.getOutputStream(), true)) {
                    output.println(Instant.now());
                }
            }
        } catch (IOException exception) {
            System.err.println("Date server failed: " + exception.getMessage());
        }
    }
}
