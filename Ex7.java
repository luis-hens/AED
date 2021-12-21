import java.util.Arrays;
import java.util.Scanner;

public class Ex7 {

    public static int max(String[] texto) {
        int max = 1;
        for (int i = 2; i < texto.length; i++) {
            if (texto[max].length() - texto[i].length() < 0)
                max = i;
        }
        return max;
    }

    public static void complete(String[] texto) {
        for (int i = 1; i < texto.length; i++) {
            if (texto[i].length() < 20)
                texto[i] = String.format("%-20.20s", texto[i]);
        }
    }

    public static void countingSort(String[] a, String[] b, int k, int d) {
        int[] c = new int[k];

        for (int i = 1; i < a.length; i++) {
            if (a[i].charAt(d) == ' ') {
                c[0]++;
            } else {
                int aux = (int) a[i].charAt(d);
                c[aux - 'a' + 1] = c[aux - 'a' + 1] + 1;
            }
        }

        for (int i = 1; i < c.length; i++) {
            c[i] = c[i] + c[i - 1];
        }

        for (int i : c) {
            System.out.print(i + " ");
        }
        System.out.println();

        for (int i = a.length - 1; i > 0; i--) {
            int aux;
            if (a[i].charAt(d) != ' ')
                aux = (int) a[i].charAt(d);
            else
                aux = (int) 'a' - 1;
            b[c[aux - 'a' + 1]] = a[i];
            c[aux - 'a' + 1] = c[aux - 'a' + 1] - 1;
        }
    }

    public static void radixSort(String[] a, int d, String[] b) {
        for (int i = d-1; i >= 0; i--) {
            countingSort(a, b, 27, i);
            a = Arrays.stream(b).toArray(String[]::new);
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n, p, m;
        n = sc.nextInt();
        sc.nextLine();

        String[] texto = new String[n + 1];
        String[] result = new String[n + 1];

        for (int i = 1; i < n + 1; i++) {
            texto[i] = sc.next();
        }

        p = sc.nextInt();
        m = sc.nextInt();

        for (int i = 1; i < n + 1; i++) {
            texto[i] = texto[i].toLowerCase();
            System.out.println(texto[i] + ".");
        }

        int d = texto[max(texto)].length();
        System.out.println(d);

        complete(texto);

        radixSort(texto, d, result);

        for (int i = p; i < p+m; i++) {
            System.out.println(result[i]);
        }

        sc.close();
    }
}