import java.util.*;
import java.io.*;

public class gen {

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
		number_test = 1;

		PrintWriter out;

		edges = new ArrayList<Edge>();
		edges1 = new ArrayList<Edge>();

		int n_copy = n;

		for (int i = 1; i <= n_copy; i++) {
			edges.clear();

			edges.add(new Edge(1, 2));
			edges.add(new Edge(2, 3));
			edges.add(new Edge(3, 1));
			numb = 4;

			n = i;

			gen(1, 1, 2, 3);

			out = new PrintWriter(toString(number_test) + ".in");

			out.println((numb - 1) + " " + edges.size());

			for (Edge q : edges) {
				out.println(q.from + " " + q.to);
			}

			out.close();

			out = new PrintWriter(toString(number_test) + ".out");
			out.println(edges.size());

			number_test++;

			out.close();
		}

		rand = new Random();

		for (int i = 1; i <= n_copy; i++) {
			edges.clear();
			edges1.clear();

			edges.add(new Edge(1, 2));
			edges.add(new Edge(2, 3));
			edges.add(new Edge(3, 1));
			numb = 4;

			n = i;

			gen(1, 1, 2, 3);

			out = new PrintWriter(toString(number_test) + ".in");

			for (Edge q : edges) {
				if (rand.nextDouble() > 0.1) {
					edges1.add(q);
				}
			}

			out.println((numb - 1) + " " + edges1.size());

			for (Edge q : edges1) {
				out.println(q.from + " " + q.to);
			}

			out.close();

			out = new PrintWriter(toString(number_test) + ".out");
			out.println(edges1.size());

			number_test++;

			out.close();
		}

		boolean used[] = new boolean[1001];
		TreeMap<Integer, Integer> mp = new TreeMap();

		for (int i = 1; i <= n_copy; i++) {
			edges.clear();

			edges.add(new Edge(1, 2));
			edges.add(new Edge(2, 3));
			edges.add(new Edge(3, 1));
			numb = 4;

			n = i;

			gen(1, 1, 2, 3);

			Arrays.fill(used, false);

			for (int j = 1; j < numb; j++) {
				if (rand.nextDouble() > 0.07) {
					used[j] = true;
				}
			}

			int cnt1 = 0;
			int cnt2 = 0;

			mp.clear();

			for (int j = 1; j < numb; j++) {
				if (used[j]) {
					cnt1++;
					mp.put(j, cnt1);
				}
			}

			for (Edge q : edges) {
				if (used[q.to] && used[q.from]) {
					cnt2++;
				}
			}

			out = new PrintWriter(toString(number_test) + ".in");

			out.println((cnt1) + " " + cnt2);

			for (Edge q : edges) {
				if (used[q.from] && used[q.to]) {
					out.println(mp.get(q.from) + " " + mp.get(q.to));
				}
			}

			out.close();

			out = new PrintWriter(toString(number_test) + ".out");
			out.println(cnt2);

			number_test++;

			out.close();
		}

		qw = new TreeSet<Pair>();

		for (int i = 1; i <= n_copy; i++) {
			edges.clear();
			qw.clear();

			edges.add(new Edge(1, 2));
			edges.add(new Edge(2, 3));
			edges.add(new Edge(3, 1));
			numb = 4;

			n = i;

			gen(1, 1, 2, 3);

			int ansm = edges.size();

			for (Edge l : edges) {
				qw.add(new Pair(Math.min(l.to, l.from), Math.max(l.to, l.from)));
			}

			out = new PrintWriter(toString(number_test) + ".in");

			int to = 0;
			
			if ((numb - 1) * (numb - 2) / 2 - ansm > 0) {
				to = rand.nextInt((numb - 1) * (numb - 2) / 2 - ansm);
			}
			
			int cur = 1;
			int cur1 = 2;

			for (int j = 0; j < to; j++) {
				while (qw.contains(new Pair(Math.min(cur, cur1), Math.max(cur, cur1)))) {
					cur1++;
					if (cur1 == i + 1) {
						cur++;
						cur1 = cur + 1;
					}
				}

				qw.add(new Pair(Math.min(cur, cur1), Math.max(cur, cur1)));
				edges.add(new Edge(cur, cur1));
				cur1++;
				if (cur1 == i + 1) {
					cur++;
					cur1 = cur + 1;
				}
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
