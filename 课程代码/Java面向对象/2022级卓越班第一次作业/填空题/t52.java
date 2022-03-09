import java.util.Scanner;
public class t52 {
    public static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        int n = sc.nextInt();
        double x=fun(n);
        System.out.printf("%f",x);
    }
    public static double fun(int m){
        double t=1;
        int i;
        for(i=2;i<m||i==m;i++){
            t=t-1.0/(i*i);
        }
        return t;
    }
}

