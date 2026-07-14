final class Sum {
    private int value;

    public int getValue() {
        return value;
    }

    public void setValue(int value) {
        this.value = value;
    }
}

final class Summation implements Runnable {
    private final int upper;
    private final Sum result;

    Summation(int upper, Sum result) {
        this.upper = upper;
        this.result = result;
    }

    @Override
    public void run() {
        int total = 0;
        for (int i = 1; i <= upper; i++) {
            total += i;
        }
        result.setValue(total);
    }
}

public class Driver {
    public static void main(String[] args) throws InterruptedException {
        if (args.length != 1) {
            System.err.println("Usage: java Driver <non-negative integer>");
            return;
        }

        int upper;
        try {
            upper = Integer.parseInt(args[0]);
        } catch (NumberFormatException exception) {
            System.err.println("Argument must be an integer.");
            return;
        }
        if (upper < 0) {
            System.err.println("Argument must be >= 0.");
            return;
        }

        Sum result = new Sum();
        Thread worker = new Thread(new Summation(upper, result), "summation");
        worker.start();
        worker.join();
        System.out.printf("The sum from 1 to %d is %d%n",
                          upper, result.getValue());
    }
}
