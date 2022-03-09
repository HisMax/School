import java.util.Scanner;
import java.math.BigDecimal;
import java.math.RoundingMode;
//😇 Java浮点数运算有精度误差，所以我们用 BigDecimal
public class t1{
    public static void main(String[] args) {
        String a,b,c,d;
        Scanner input = new Scanner(System.in);//读入实例
        a = input.next();
        b = input.next();
        BigDecimal a1 = new BigDecimal(a);
        BigDecimal b1 = new BigDecimal(b);
        BigDecimal a2 = new BigDecimal("0.45359237");
        BigDecimal b2 = new BigDecimal("0.0254");
        c = a1.divide(a2,7,RoundingMode.HALF_UP).stripTrailingZeros().toPlainString();
        d = b1.divide(b2,5,RoundingMode.HALF_UP).stripTrailingZeros().toPlainString();
        if(c.contains(".")==true)System.out.printf("%s ",c);
        else System.out.printf("%s.0 ",c);
        if(d.contains(".")==true)System.out.printf("%s",d);
        else System.out.printf("%s.0",d);
    }
}
