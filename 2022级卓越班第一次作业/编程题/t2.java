
import java.math.BigDecimal;
import java.math.BigInteger;
import java.util.Scanner;
public class t2{
    public static void main(String[] args) {
        int a,b,c;double d;
        int m = 10000;double esp = 1e-6;
        double tx1,tx2,tx3,tx4;
        Scanner scan = new Scanner(System.in);
        a = scan.nextInt();
        b = scan.nextInt()*m;
        c = scan.nextInt()*m;
        d = scan.nextDouble();
        tx4 = d*1.36;
        tx3 = d*3.0;
        tx2 = b*0.05*0.01;
        if(a==1){
            if(d<90.0||Math.abs(d-90.0)<esp){
                tx1 = (c*0.01) ;
            }
            else if(d<144.0||Math.abs(d-144.0)<esp){
                tx1 = c*0.015;
            }
            else tx1 = c*0.03;
        }
        else tx1 = c*0.03;
        System.out.printf("%s %s %s %s",ero(tx1),ero(tx2),ero(tx3),ero(tx4));
    }
    public static String ero(double x){
        String ans;
        x = (double) Math.round(x * 1000) / 1000;
        BigDecimal p = new BigDecimal(x+"");
        ans = p.stripTrailingZeros().toPlainString();
        if(ans.contains("."))return ans;
        else return ans+".0";
    }
}
