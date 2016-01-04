import java.util.*;
import java.io.*;

public class gen2 {
	static Random rand;

	static class Edge {
		int from;
		int to;

		Edge(int _from, int _to) {
			from = _from;
			to = _to;
		}
	}

	static int n;
	static int number_test;
	static ArrayList<Edge> edges;
	static ArrayList<Edge> edges1;
	static int numb;

	static class Pair implements Comparable<Pair> {
		int x;
		int y;

		Pair(int _x, int _y) {
			x = _x;
			y = _y;
		}

		@Override
		public int compareTo(Pair o) {
			if (this.x == o.x) {
				return this.y - o.y;
			} else {
				return this.x - o.x;
			}
		}
	}

	static TreeSet<Pair> qw;

	static void gen(int cnt, int a, int b, int c) {
		if (cnt == n) {
			return;
		} else {
			edges.add(new Edge(a, numb));
			edges.add(new Edge(b, numb));
			edges.add(new Edge(c, numb));
			int curnumb = numb;
			numb++;
			gen(cnt + 1, a, b, curnumb);
			gen(cnt + 1, c, b, curnumb);
			gen(cnt + 1, a, c, curnumb);
		}
	}

	static String toString(int a) {
		int a1 = a;

		String s = "";

		while (a1 > 0) {
			s = (char) ((a1 % 10) + (int) '0') + s;
			a1 /= 10;
		}

		return s;
	}

	public static void main(String[] args) throws FileNotFoundException {
		Scanner in = new Scanner(System.in);

		System.out.println("Enter deep");
		n = in.nextInt();
		number_test = 29;

		PrintWriter out;

		edges = new ArrayList<Edge>();
		
		int n_copy = n;
		
		rand = new Random();
		
		qw = new TreeSet<Pair>();

		for (int i = 1; i <= n_copy; i++) {
			edges.clear();
			
			for (int j = 1; j <= 6; j++) {
				for (int j1 = j + 1; j1 <= 7; j1++) {
					qw.add(new Pair(j, j1));
				}
			}

			edges.add(new Edge(1, 2));
			edges.add(new Edge(2, 3));
			edges.add(new Edge(3, 1));
			numb = 4;

			n = 3;

			gen(1, 1, 2, 3);

			int ansm = edges.size();

			for (Edge l : edges) {
				qw.remove(new Pair(Math.min(l.to, l.from), Math.max(l.to, l.from)));
			}

			out = new PrintWriter(toString(number_test) + ".in");

			int to = rand.nextInt(6);
			
			for (int j = 0; j < to; j++) {
				int ct = rand.nextInt(qw.size());
				int cur1 = 1;
				int cur = 0;
				
				int cnt = 0;
				for (Pair l: qw) {
					cnt++;
					if (cnt == ct){
						cur = l.x;
						cur1 = l.y;
					}
				}

				qw.remove(new Pair(Math.min(cur, cur1), Math.max(cur, cur1)));
				edges.add(new Edge(cur, cur1));
			}

			out.println((numb - 1) + " " + edges.size());

			for (Edge q : edges) {
				out.println(q.from + " " + q.to);
			}

			out.close();

			out = new PrintWriter(toString(number_test) + ".out");
			out.println(ansm);

			number_test++;

			out.close();
		}

	}
}
