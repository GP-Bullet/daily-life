import java.util.*;
public class Main {
    public static void main(String [] args){
        Scanner c= new Scanner(System.in);
        int n  = c.nextInt();
        String blank = c.nextLine();
        String str [] = c.nextLine().split("");
        int vk =0;
        int vv = 0, kk =0;

        for(int i = 0; i< n-1; i++) {
            if(str[i].equals("C") && str[i+1].equals("V"))  {
                vk++;
                str[i] = "X";
                str[i +1] = "X";
            }
        }

        for(int i =0; i < n-1; i++){
            if(str[i].equals("C")&& str[i+1].equals("C")  ) vv++;
            if(str[i].equals("V") && str[i+1].equals("V")  ) kk++;
        }
        
        if(vv!=0 ||kk!=0){
            System.out.println(vk+1);
        }
         else if(vv==0 && kk==0){
            System.out.println(vk);
        }
    }}