/**
 * Homework Assignment #6: "8-Puzzle"
 *
 *  - Solver class for solving "8-Puzzle" Programming Assignment
 *
 *  Compilation:  javac Solver.java Board.java
 *  Execution:    java Solver inputfile.txt
 *  Dependencies: MinPQ
 *
 * @ Student ID : 20145523
 * @ Name       : KimSangHeon
 **/

import java.io.File;
import java.util.Scanner;

public class Solver {
    private boolean solved;
    private Node solution;
    private int minMoves;
    // search node
    private class Node implements Comparable<Node> {
        private Board board;
        private int moves;
        private Node prev;

        public Node(Board board, int moves, Node prev) {
            if (board == null)
                throw new java.lang.NullPointerException();
            this.board = board;
            this.moves = moves;
            this.prev = prev;
        }

        // calculate distance of this search node
        public int distance() {
            return this.board.manhattan() + moves;
        }

        // calculate priority of this search node
        public int priority() {
            return (distance() + 2 * this.board.linearConflict());
        }

        // compare node by priority (implements Comparable<Node>)
        @Override
        public int compareTo(Node that) {
            return this.priority() - that.priority();
        }
    }

    // find a solution to the initial board (using the A* algorithm)
    public Solver(Board initial) {
        if (initial == null)
            throw new java.lang.NullPointerException();

        solved = false;
        solution = null;
        minMoves = -1;
        // create initial search node
        Node initNode = new Node(initial, 0, null);
        // priority queue
        MinPQ<Node> minPQ = new MinPQ<Node>();
        // insert the initial search node into a priority queue
        minPQ.insert(initNode);
        // solve the puzzle
        while ( !minPQ.isEmpty() ) {
            Node now = minPQ.delMin();
            // Check it is unsolvable
            if ( now.board.twin().isGoal() ) break;
            // If it is goal
            if ( now.board.isGoal() ) {
                solved = true;
                if ( minMoves == -1 || now.moves < minMoves) {
                    minMoves = now.moves;
                    solution = now;
                }
                // If it is a goal, we don't have to go again
                continue;
            }
            // If it is worthy to go deep
            if ( minMoves == -1 || now.priority() < minMoves) {
                for (Board b : now.board.neighbors()) {
                    // add to minPQ except previous one
                    if (now.prev == null || !b.equals(now.prev.board)) {
                        minPQ.insert(new Node(b, now.moves + 1, now));
                    }
                }
            }
        }
    }
    // is the initial board solvable?
    public boolean isSolvable() {
        return solved;
    }
    // min number of moves to solve initial board; -1 if unsolvable
    public int moves() {
        return minMoves;
    }
    // sequence of boards in a intest solution; null if unsolvable
    public Iterable<Board> solution() {
        if (solution == null)
            return null;
        Stack<Board> sol = new Stack<Board>();
        Node searchNode = solution;
        while (searchNode != null) {
            sol.push(searchNode.board);
            searchNode = searchNode.prev;
        }
        return sol;
    }

    // solve a slider puzzle (given below)
    public static void main(String[] args) {

        // to calculate running time
        long start = System.currentTimeMillis();
        double time;

        // read the input file
        Scanner in;
        String filename = args[0];
        try {
            in = new Scanner(new File(args[0]), "UTF-8");
        } catch (Exception e) {
            System.out.println("invalid or no input file ");
            return;
        }

        // create initial board from file
        int N = in.nextInt();
        int[][] blocks = new int[N][N];

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                blocks[i][j] = in.nextInt();
                if (blocks[i][j] >= N*N)
                    throw new IllegalArgumentException("value must be < N^2");
                if (blocks[i][j] < 0)
                    throw new IllegalArgumentException("value must be >= 0");
            }
        }

        // initial board
        Board initial = new Board(blocks);

        // solve the puzzle
        Solver solver = new Solver(initial);

        // print solution to standard output
        if (!solver.isSolvable())
            System.out.println("No solution possible");
        else {
            System.out.println("Minimum number of moves = " + solver.moves() + "\n");
            for (Board board : solver.solution())
                System.out.println(board);
        }

        // calculate running time
        time = (System.currentTimeMillis() - start) / 1000.0;
        System.out.println("time = "+ time + "sec");
        System.out.println("Minimum number of moves = " + solver.moves() + "\n");
    }
}

