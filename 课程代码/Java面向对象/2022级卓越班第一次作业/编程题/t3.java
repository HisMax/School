import java.math.BigDecimal;
import java.math.RoundingMode;
import java.util.Scanner;

public class t3 {
    /*public static void main(String[] args) {
        double l,n;
        Scanner scan = new Scanner(System.in);
        n = scan.nextDouble();
        l = scan.nextDouble();
        if(n<0.0||l<0.0||Math.abs(l-0.0)<1e-6){System.out.printf("Wrong Format");return;}
        BigDecimal n = new BigDecimal(n+"");
        BigDecimal lg = new BigDecimal(l+"");
        BigDecimal ng = new BigDecimal("-114514.0");
        BigDecimal esp = new BigDecimal(0.00001+"");
        while(true){
            ng = lg.add(n.divide(lg,8,RoundingMode.HALF_EVEN)).divide(new BigDecimal("2.0"),8,RoundingMode.HALF_UP);
            
            if(ng.subtract(lg).abs().compareTo(esp)==-1)break;
            lg = ng;
            //System.out.println(ng.toPlainString());
        }
        System.out.printf("%.7f",lg.stripTrailingZeros().add(new BigDecimal("0.00000005")));
    }*/
    public static void main(String[] args) {
        float n,lg,ng,eps = 0.00001f;
        Scanner scan = new Scanner(System.in);
        n = scan.nextFloat();
        lg = scan.nextFloat();
        ng = (lg+n/lg)/2;
        if(n<=0||lg<=0){System.out.printf("Wrong Format");return;}
        while(Math.abs(ng-lg)>=eps){
            lg = ng;
            ng = (lg+n/lg)/2;
            if(Math.abs(ng-lg)<eps)break;
        }
        System.out.print(lg);
    }
}
