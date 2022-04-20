package test;

public class Test{
   public static void main(String[] args) {
      Test t = new Test();
      t.show(new Car(){
         public void run(){
            System.out.println("test run");
         }
      });
   }
   public void show(Car c){
      c.run();
      c.show();
}}
abstract class Car{
   public void run(){
      System.out.println("car run");
   }
   public void show(){
       System.out.println(getClass().getName());
}}