/**
 * Homework Assignment #6: "8-Puzzle"
 *
 *  - Board class for solving "8-Puzzle" Programming Assignment
 *
 *  Compilation:  javac Board.java Queue.java
 *
 * @ Student ID : 20145523
 * @ Name       : KimSangHeon
 **/

import java.io.File;
import java.util.Scanner;
import java.util.Arrays;

public class Board {
    private int[][] tiles;
    private int N;
    private int blanki;
    private int blankj;
    private int manhattan;
    private int linearN;

    // construct a board from an N-by-N array of blocks
    // (where blocks[i][j] = block in row i, column j)
    public Board(int[][] blocks) {
        if (blocks == null)
            throw new java.lang.NullPointerException();

        N = blocks.length;
        if (N < 2 || N > 128)
            throw new IllegalArgumentException("N must be <= 128");

        tiles = new int[N][N];
        for (int i = 0; i < N; i++) 
            System.arraycopy(blocks[i], 0, tiles[i], 0, blocks[i].length);
        // Setting manhattan distance & blank i,j & linearConflict
        calValues();
    }
    private void calValues() {
        manhattan = 0;
        linearN = 0;
        blanki = 0;
        blankj = 0;
        // the Answet tile
        int tileN = 0;
        for ( int i = 0; i < N; i ++) {
            for ( int j = 0; j < N; j++) {
                tileN++;
                // If this tile is blank
                if (tiles[i][j] == 0) {
                    blanki = i;
                    blankj = j;
                    continue;
                }
                if (tiles[i][j] == tileN) continue;
                int col = (tiles[i][j] - 1) / N;
                int row = (tiles[i][j] - 1) % N;
                // calculate manhattan
                manhattan += Math.abs(col - i)
                                 + Math.abs(row - j);
                                 
                // If line conflict happens in column
                if (col == i) {
                    for ( int a = j; a < N; a++) {
                        if (tiles[i][a] == tileN ) {
                            int goal = i * N + a + 1;
                            for ( int b = a; b >= j; b--) {
                                // When we finally find linear conflict
                                if(tiles[i][b] == goal){
                                    linearN++;
                                    break;
                                }
                            }
                            break;
                        }
                    }
                }
                // If line conflict happens in row
                if ( row == j) {
                    for ( int a = i; a < N; a++) {
                        if(tiles[a][j] == tileN) {
                            int goal = a * N + j + 1;
                            for (int b = a; b >= i; b--) {
                                if(tiles[b][j] == goal) {
                                    linearN++;
                                    break;
                                }
                            }
                            break;
                        }
                    }
                }
            }
        }
    }

    // board dimension N
    public int dimension() {
        return N;
    }
    // sum of linear conflict between blocks
    public int linearConflict() {
        if( tiles[blanki][blankj] != 0) calValues();
        return linearN;
    }
    // sum of Manhattan distances between blocks and goal
    public int manhattan() {
        if ( tiles[blanki][blankj] != 0 ) calValues();
        return manhattan;
    }
    // is this board the goal board?
    public boolean isGoal() {
        int answer = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                answer++;
                if (tiles[i][j] != answer 
                    && (i != N-1 || j != N-1)) {
                    return false;
                }
            }
        }
        return true;
    }

    private void swap(int[][] blocks, int r1, int c1, int r2, int c2) {
        if (r1 < 0 || c1 < 0 || r2 < 0 || c2 < 0)
            throw new IndexOutOfBoundsException("row/col index < 0");
        if (r1 >= N || c1 >= N || r2 >= N || c2 >= N)
            throw new IndexOutOfBoundsException("row/col index >= N");
        // swap blocks
        blocks[r1][c1] = blocks[r1][c1] ^ blocks[r2][c2];
        blocks[r2][c2] = blocks[r1][c1] ^ blocks[r2][c2];
        blocks[r1][c1] = blocks[r1][c1] ^ blocks[r2][c2];
    }

    // a board that is obtained by exchanging two adjacent blocks in the same row
    public Board twin() {
        int[][] blocks = new int[N][N];
        for (int i = 0; i < N; i++)
            System.arraycopy(tiles[i], 0, blocks[i], 0, tiles[i].length);
        for ( int i = 0; i < N ; i++) {
            if ( blocks[i][0] != 0 && blocks[i][1] != 0) {
                swap(blocks, i, 0, i, 1);
                return new Board(blocks);
            }
        }
        return new Board(blocks);
    }

    // does this board equal y?
    public boolean equals(Object y) {
        if ( y == null) return false;
        if ( y.getClass() != this.getClass() ) return false;
        Board x = (Board) y;
        if ( x.dimension() != this.dimension()) return false;
        return Arrays.deepEquals(tiles, x.tiles);
    }

    // all neighboring boards
    public Iterable<Board> neighbors() {

        Queue<Board> nbrs = new Queue<Board>();
        // put all neighbor boards into the queue
        if ( blanki < N - 1) {
            swap(tiles, blanki, blankj, blanki + 1, blankj);
            nbrs.enqueue(new Board(tiles));
            swap(tiles, blanki, blankj, blanki + 1, blankj);            
        }
        if (blankj < N - 1) {
            swap(tiles, blanki, blankj, blanki, blankj + 1);
            nbrs.enqueue(new Board(tiles));
            swap(tiles, blanki, blankj, blanki, blankj + 1);
        }
        if (blankj > 0) {
            swap(tiles, blanki, blankj, blanki, blankj - 1);
            nbrs.enqueue(new Board(tiles));
            swap(tiles, blanki, blankj, blanki, blankj - 1);
        }
        if (blanki > 0) {
            swap(tiles, blanki, blankj, blanki - 1, blankj);
            nbrs.enqueue(new Board(tiles));
            swap(tiles, blanki, blankj, blanki - 1, blankj);
        }
        return nbrs;
    }

    // string representation of this board (in the output format specified below)
    public String toString() {
        StringBuilder s = new StringBuilder();
        s.append(N + "\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                s.append(String.format("%2d ", tiles[i][j]));
            }
            s.append("\n");
        }
        return s.toString();
    }

    // unit tests (DO NOT MODIFY)
    public static void main(String[] args) {
        // read the input file
        Scanner in;
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
                blocks[i][j] = (int)in.nextInt();
                if (blocks[i][j] >= N*N)
                    throw new IllegalArgumentException("value must be < N^2");
                if (blocks[i][j] < 0)
                    throw new IllegalArgumentException("value must be >= 0");
            }
        }

        Board initial = new Board(blocks);

        System.out.println("\n=== Initial board ===");
        System.out.println(" - manhattan = " + initial.manhattan());
        System.out.println(initial.toString());

        Board twin = initial.twin();

        System.out.println("\n=== Twin board ===");
        System.out.println(" - manhattan = " + twin.manhattan());
        System.out.println(" - equals = " + initial.equals(twin));
        System.out.println(twin.toString());

        System.out.println("\n=== Neighbors ===");
        for (Board board : initial.neighbors())
            System.out.println(board);
    }
}