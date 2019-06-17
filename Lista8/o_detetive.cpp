import java.util.ArrayList;
import java.util.Scanner;

public class Main {
    
   static void knapSack(int V[], int W[], int K)
   {
       int D[][] = new int[V.length+1][K+1];

       for (int i = 1; i <= V.length; i++) {
           for (int j = 1; j <= K ; j++) {
               if(W[i-1] <= j){
                   D[i][j] = Math.max(D[i-1][j], V[i-1] + D[i-1][j - W[i-1]]);
               } else {
                   D[i][j] = D[i-1][j];
               }
           }
       }

       int res = D[V.length][K];

       ArrayList<Integer> bags = new ArrayList<Integer>();

       int w = K;
       for (int i = V.length; i > 0 && res > 0; i--) {


           if (res == D[i - 1][w])
               continue;
           else {

               bags.add((i - 1));

               res = res - V[i - 1];
               w = w - W[i - 1];
           }
       }
      
       System.out.println(D[V.length][K]);
       
       for (int i = bags.size() - 1; i >= 0; i--){
           if(i != 0)
        	   System.out.print(bags.get(i) + " ");
           else
        	   System.out.print(bags.get(i)+ "\n");
       }
   }

   public static void main(String[] args) {
       Scanner in = new Scanner(System.in);

       int n = in.nextInt();
       int k = in.nextInt();

       int V[] = new int[n];
       int W[] = new int[n];

       for (int i = 0; i < n; i++){
           V[i] = in.nextInt();
           W[i] = in.nextInt();
       }

       knapSack(V, W, k);
   }

}


