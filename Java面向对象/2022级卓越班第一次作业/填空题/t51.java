import java.util.Scanner;
public class t51 {
    public static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        String str=sc.nextLine();
        char x[]=str.toCharArray();
        int a=0;
        int b=0;
        int c=0;
        int d=0;
        for(int i=0;i<x.length;i++){
            char ch=x[i];
            if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z'))
                a++;
            else if(ch>='0'&&ch<='9')
                b++;
            else if(ch==' ')
                c++;
            else d++;
        }
        System.out.println("letters="+a);//输出英文字母个数
        System.out.println("digits="+b);//输出数字个数
        System.out.println("spaces="+c);//输出空格个数
        System.out.println("others="+d);//输出其他字符个数
    }
}
