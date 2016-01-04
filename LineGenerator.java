import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Random;
import java.util.StringTokenizer;

public class LineGenerator {

	public static void main(String[] args) throws IOException {
		new LineGenerator().run();
	}

	FastScanner in;
	PrintWriter out;

	void run() throws IOException {
		in = new FastScanner(System.in);
		out = new PrintWriter(System.out);
		solve();
		out.close();
	}

	final double eps = 1e-8;

	final int linesArraySize = 10;

	Line lines[];
	ArrayList<Point> points;
	ArrayList<Edge> edges;
	int freePointId;
	int degree[];
	boolean graph[][];

	Random random;

	void solve() throws IOException {
		lines = new Line[linesArraySize];
		random = new Random();
		for (int i = 0; i < linesArraySize; i++) {
			double a = 1.0 - 2.0 * random.nextDouble();
			double b = 1.0 - 2.0 * random.nextDouble();
			double c = random.nextDouble() * (random.nextInt() % 40000);
			lines[i] = new Line(a, b, c);
		}

		points = new ArrayList<Point>();
		edges = new ArrayList<Edge>();
		freePointId = 0;

		for (int i = 0; i < linesArraySize; i++) {
			ArrayList<Point> pointsOnLine = new ArrayList<Point>();
			for (int j = i + 1; j < linesArraySize; j++) {
				Point P = cross(lines[i], lines[j]);
				points.add(P);
				freePointId++;
			}
			Collections.sort(pointsOnLine);
			for (int j = 0; j + 1 < pointsOnLine.size(); j++) {
				Point P1 = pointsOnLine.get(j);
				Point P2 = pointsOnLine.get(j + 1);
				edges.add(new Edge(P1.id, P2.id));
			}
		}

		for (int i = 0; i < linesArraySize; i++) {
			ArrayList<Point> pointsOnLine = new ArrayList<Point>();
			for (int j = 0; j < points.size(); j++) {
				if (onLine(lines[i], points.get(j)))
					pointsOnLine.add(points.get(j));
			}
			Collections.sort(pointsOnLine);
			for (int j = 0; j + 1 < pointsOnLine.size(); j++) {
				edges.add(new Edge(pointsOnLine.get(j).id, pointsOnLine
						.get(j + 1).id));
			}
		}

		int n = points.size();
		int m = points.size();
		degree = new int[n];
		graph = new boolean[n][n];

		for (int i = 0; i < m; i++) {
			degree[edges.get(i).v]++;
			degree[edges.get(i).u]++;
			graph[edges.get(i).v][edges.get(i).u] = true;
			graph[edges.get(i).u][edges.get(i).v] = true;
		}
		for (int v = 0; v < n; v++) {
			if (degree[v] == 0) {
				int u = v;
				while (u == v)
					u = Math.abs(random.nextInt()) % n;
				edges.add(new Edge(v, u));
				graph[v][u] = true;
				graph[u][v] = true;
			}
		}

		int maxIt = 100000;
		int randomEdgesSize = random.nextInt() % (m / 2);
		for (int i = 0; i < randomEdgesSize && maxIt > 0; i++) {
			int v = -1, u = -1;
			while (maxIt > 0 && (v == u || graph[v][u])) {
				v = Math.abs(random.nextInt()) % n;
				u = Math.abs(random.nextInt()) % n;
				maxIt--;
			}
			if (maxIt != 0) {
				edges.add(new Edge(v, u));
				graph[v][u] = true;
				graph[u][v] = true;
				m++;
			}
		}

		// for (int i = 0; i < points.size(); i++) {
		// out.println(points.get(i).x + " " + points.get(i).y + " " +
		// points.get(i).id);
		// }

		out.println(n + " " + m);
		for (int i = 0; i < edges.size(); i++) {
			out.println((edges.get(i).v + 1) + " " + (edges.get(i).u + 1));
		}

	}

	class Point implements Comparable<Point> {
		double x, y;
		int id;
		boolean isGood;

		Point(double x, double y, int id) {
			this.x = x;
			this.y = y;
			this.id = id;
			this.isGood = Math.max(Math.abs(x), Math.abs(y)) < 300.0;
		}

		@Override
		public int compareTo(Point o) {
			if (Math.abs(x - o.x) < eps && Math.abs(y - o.y) < eps)
				return 0;
			if (Math.abs(x - o.x) > eps)
				return x < o.x - eps ? -1 : 1;
			return y < o.y - eps ? -1 : 1;
		}

	}

	class Line {
		double a, b, c;

		Line(Point A, Point B) {
			this.a = A.y - B.y;
			this.b = B.x - A.x;
			this.c = -a * A.x - b * A.y;
		}

		Line(double a, double b, double c) {
			this.a = a;
			this.b = b;
			this.c = c;
		}
	}

	class Edge {
		int v, u;

		Edge(int v, int u) {
			this.v = v;
			this.u = u;
		}
	}

	Point cross(Line L1, Line L2) {
		double x = (L1.b * L2.c - L2.b * L1.c) / (L1.a * L2.b - L2.a * L1.b);
		double y = (L1.a * L2.c - L2.a * L1.c) / (L2.a * L1.b - L1.a * L2.b);
		return new Point(x, y, freePointId);
	}

	boolean onLine(Line L, Point P) {
		return Math.abs(L.a * P.x + L.b * P.y + L.c) < eps;
	}

	class FastScanner {

		BufferedReader br;
		StringTokenizer st;

		FastScanner(InputStream in) {
			br = new BufferedReader(new InputStreamReader(in));
			st = null;
		}

		FastScanner(String in) throws FileNotFoundException {
			br = new BufferedReader(new FileReader(new File(in)));
			st = null;
		}

		String next() throws IOException {
			while (st == null || !st.hasMoreTokens())
				st = new StringTokenizer(br.readLine());
			return st.nextToken();
		}

		int nextInt() throws IOException {
			return Integer.parseInt(next());
		}

		long nextLong() throws IOException {
			return Long.parseUnsignedLong(next());
		}

	}

}
