import java.util.Scanner;
import java.math.BigDecimal;
import java.math.RoundingMode;
//😇 Java浮点数运算有精度误差，所以我们用 BigDecimal
public class t1{
    public static void main(String[] args) {
        double a = 0.0,b = 0.0;
        Scanner input = new Scanner(System.in);//读入实例
        a = input.nextDouble();
        b = input.nextDouble();
        BigDecimal a1 = new BigDecimal(a+"");
        BigDecimal b1 = new BigDecimal(b+"");
        BigDecimal a2 = new BigDecimal(0.4535922921969+"");
        BigDecimal b2 = new BigDecimal(0.025400000000102+"");
        System.out.printf("%s %s",a1.divide(a2,2,RoundingMode.HALF_UP).stripTrailingZeros().toPlainString(),b1.divide(b2,2,RoundingMode.HALF_UP).stripTrailingZeros().toPlainString());
    }
}

