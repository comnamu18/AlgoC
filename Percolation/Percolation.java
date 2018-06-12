/**
 * Homework Assignment #4: Percolation
 *
 *  - Percolation data structure
 *
 * @ Student ID : 20145523
 * @ Name       : KimSangHeon
 **/

import java.util.Scanner;
import java.io.File;

public class Percolation {

    private static final boolean SITE_BLOCKED = false;
    private static final boolean SITE_OPEN = true;
    private boolean[] sites;          // sites[i] = state of site i
    private int mN;                   // remember the input N
    private int topIdx;               // idx of the special top
    private int bottomIdx;            // idx of the speical bottom
    private WeightedQuickUnionUF uf;
    // Additional Tree needed to check Full
    private WeightedQuickUnionUF chkFull;
    
    // create N-by-N grid, with all sites blocked
    public Percolation(int N) {
        if (N <= 0)
            throw new IllegalArgumentException("N must be >0");
        mN = N;

        sites = new boolean[N * N];
        uf = new WeightedQuickUnionUF(N * N + 2);
        // Since Full needs special top only
        chkFull = new WeightedQuickUnionUF(N * N + 1);
        topIdx = N * N;
        bottomIdx = N * N + 1;
        // Set default Value
        for ( int i = 0; i < N * N; i++ ) {
            sites[i] = SITE_BLOCKED;
        }
        // Set special top and bottom tree node
        for ( int i = 0; i < N; i++ ) {
            uf.union(topIdx, i);
            uf.union(bottomIdx, mN * mN - i - 1);
            chkFull.union(topIdx, i);
        }
    }

    private void checkIndex(int i, int j) {
        if (i < 1 || i > mN)
            throw new IndexOutOfBoundsException("row index i out of bounds");
        if (j < 1 || j > mN)
            throw new IndexOutOfBoundsException("column index j out of bounds");
    }

    // open site(row i, column j) if it is not open already
    public void open(int i, int j) {
        // Translate (i, j) to tN for Tree's array
        int tN = mN * (i - 1) + (j - 1);
        // If it is already opened, then just end function
        if (isOpen(i, j)) return;
        
        sites[tN] = SITE_OPEN;
        //To connect surrounded opened sites
        if ( j > 1 && isOpen(i, j - 1) ) {//When Left connected
            uf.union(tN, tN - 1);
            chkFull.union(tN, tN - 1);
        }
        if ( j < mN && isOpen(i, j + 1) ) {//When Right connected
            uf.union(tN, tN + 1);
            chkFull.union(tN, tN + 1);
        }
        if ( i < mN && isOpen(i + 1, j) ) {//When Down connected
            uf.union(tN, tN + mN);
            chkFull.union(tN, tN + mN);
        }
        if ( i > 1 && isOpen(i - 1, j) ) {//When Up connected
            uf.union(tN, tN - mN);
            chkFull.union(tN, tN - mN);
        }
    }

    // is site(row i, column j) open?
    public boolean isOpen(int i, int j) {
        // If use i,j in this class, every Func go through this part
        checkIndex(i, j);
        return sites[mN * (i - 1) + (j - 1)];
    }

    // is site(row i, column j) full?
    public boolean isFull(int i, int j) {
        // Translate (i, j) to tN for Tree's array
        int tN = mN * (i - 1) + (j - 1);
        // If block is not opened, then it must be false
        if(!isOpen(i,j)) return false;
        return chkFull.connected(topIdx, tN);
    }

    // does the system percolate?
    public boolean percolates() {
        return uf.connected(topIdx, bottomIdx);
    }

    // test client(optional)
    public static void main(String[] args)
    {
        Scanner in;
        int N = 0;
        long start = System.currentTimeMillis();

        try {
            // get input file from argument
            in = new Scanner(new File(args[0]), "UTF-8");
        } catch (Exception e) {
            System.out.println("invalid or no input file ");
            return;
        }

        N = in.nextInt();         // N-by-N percolation system
        System.out.printf("N = %d\n", N);

        // repeatedly read in sites to open and draw resulting system
        Percolation perc = new Percolation(N);

        while (in.hasNext()) {
            int i = in.nextInt();   // get i for open site (i,j)
            int j = in.nextInt();   // get j for open site (i,j)
            perc.open(i, j);        // open site (i,j)
            System.out.printf("open(%d, %d)\n", i, j);
        }
        if (perc.percolates()) {
            System.out.println("This system percolates");
        } else {
            System.out.println("This system does NOT percolate");
        }

        double time = (System.currentTimeMillis() - start) / 1000.0;
        System.out.println("running time = "+ time + " sec");
        in.close(); // Might be not needed..
    }
}

