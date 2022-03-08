import java.util.Scanner;
import java.math.BigDecimal;
import java.math.RoundingMode;
//😇 笑死，要的就是误差
public class Main{
    public static void main(String[] args) {
        float a,b;
        Scanner scan = new Scanner(System.in);
        a = scan.nextFloat();
        b = scan.nextFloat();
        a = (float) Math.round(a/0.45359237 * 10000000) / 10000000;
        b = (float) Math.round(b/0.0254 * 100000) / 100000;
        System.out.print(a);
        System.out.print(" ");
        System.out.print(b);
    }
}