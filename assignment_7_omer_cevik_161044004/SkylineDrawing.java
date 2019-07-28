/*
											CSE 241 Homework Assignment 7

												OMER_CEVIK_161044004

					# 					In that programme, we read input file and   					 #
					# 			  we create a skyline. We print skyline outputs and drawing 			 #
					#									GUI.										  	 # 

																														*/
import javax.swing.*;
import java.io.*;
import java.util.*;
import java.awt.Graphics;
import java.awt.Color;

public class SkylineDrawing extends JFrame
{
     // Represents either start or end of skyline.
    public static int MaxScreenWidth;
    public static int MaxScreenHeight;

    public List<int[]> CreateSkyline(List<int[]> SkyLineInputs)
    {
        // For all start and end of skyline put them into List of SkylineClass.

        SkylineClass[] SkylineCorners = new SkylineClass[SkyLineInputs.size()*2];
        int index = 0;

        for(int SkyLineCornerCounter[] : SkyLineInputs)
        {
            SkylineCorners[index] = new SkylineClass();
            SkylineCorners[index].Corner = SkyLineCornerCounter[0];
            SkylineCorners[index].StartChecker = true;
            SkylineCorners[index].Height = SkyLineCornerCounter[2];

            SkylineCorners[index + 1] = new SkylineClass();
            SkylineCorners[index + 1].Corner = SkyLineCornerCounter[1];
            SkylineCorners[index + 1].StartChecker = false;
            SkylineCorners[index + 1].Height = SkyLineCornerCounter[2];
            index += 2;
        }

        // Finding maximum height to use in GUI.
        MaxScreenHeight = SkylineCorners[0].Height;

        for (int i = 1; i < SkylineCorners.length; ++i)
        {
            if ( SkylineCorners[i].Height > MaxScreenHeight )
            {
                MaxScreenHeight = SkylineCorners[i].Height;
            }
        }

        Arrays.sort(SkylineCorners);

        // Finding maximum width to use in GUI.
        MaxScreenWidth = SkylineCorners[SkylineCorners.length-1].Corner;

        //using TreeMap because it gives log time performance.

        TreeMap<Integer, Integer> queue = new TreeMap<>();
        queue.put(0, 1);

        int prevMaxHeight = 0;
        List<int[]> Output_Skyline = new ArrayList<>();

        for(SkylineClass SkylineCorner : SkylineCorners)
        {
            // If it is start of skyline then add the height to map.
            // If height already exists then increment the value.

            if (SkylineCorner.StartChecker)
            {
                queue.compute(SkylineCorner.Height, (key, value) -> {
                    if (value != null)
                    {
                        return value + 1;
                    }
                    return 1;
                });
            }
            else
            {
                // If it is end of skyline then decrement or remove the height from map.

                queue.compute(SkylineCorner.Height, (key, value) -> {
                    if (value == 1)
                    {
                        return null;
                    }
                    return value - 1;
                });
            }

            int currentMaxHeight = queue.lastKey();

            // If height changes from previous height then this skyline corner becomes output corner.
            // So add it to the Output_Skyline.

            if (prevMaxHeight != currentMaxHeight)
            {
                if (prevMaxHeight < currentMaxHeight)
                {
                    Output_Skyline.add(new int[]{SkylineCorner.Corner, prevMaxHeight});
                }
                Output_Skyline.add(new int[]{SkylineCorner.Corner, currentMaxHeight});
                prevMaxHeight = currentMaxHeight;
            }
            else if ( prevMaxHeight == currentMaxHeight )
            {
                Output_Skyline.add(new int[]{SkylineCorner.Corner, prevMaxHeight});
            }
        }

        return Output_Skyline;
    }

    public static class SkylineClass implements Comparable<SkylineClass>
    {
        private int Corner;
        private boolean StartChecker;
        private int Height;

        @Override
        public int compareTo(SkylineClass o)
        {
            // First compare by Corner.
            // If they are same then use this logic:
            //   If two starts are compared then higher height skyline should be picked first.
            //   If two ends are compared then lower Height skyline should be picked first.
            //   If one start and end is compared then start should appear before end.
            if (this.Corner != o.Corner)
            {
                return this.Corner - o.Corner;
            }
            else
            {
                return (this.StartChecker ? -this.Height : this.Height) - (o.StartChecker ? -o.Height : o.Height);
            }
        }
     }
     
    /* It reads data.txt file into List<int[]> and creates skyline's most important datas.	*/

    public static void ReadFile(List<int[]> SkyLineInputs)
    {
        Scanner InputFile = null;
        try
        {
            InputFile = new Scanner(new BufferedReader(new FileReader("data.txt")));
            int ValueCounter = 0, inputHeight = 0, inputWidth = 0, inputPosition = 0;

            while ( InputFile.hasNext() )
            {
                if ( InputFile.hasNextInt() )
                {
                    switch(ValueCounter%4)
                    {
                        case 0: inputWidth = InputFile.nextInt();
                        break;

                        case 1: inputHeight = InputFile.nextInt();
                        break;

                        case 2: inputPosition = InputFile.nextInt();
                        break;

                        case 3: SkyLineInputs.add(new int[]{inputPosition,inputPosition+inputWidth,inputHeight});
                        break;
                    }
                    ++ValueCounter;
                }
            }

            SkyLineInputs.add(new int[]{inputPosition,inputPosition+inputWidth,inputHeight});
        }
        catch (FileNotFoundException e)
        {
            e.printStackTrace();
        }
        finally
        {
            if ( InputFile != null )
            {
                InputFile.close();
            }
        }
    }

    public void WriteToFile(List<int[]> SkyLineOutputs)	// It writes outputs into output.txt.
    {
        try
        {
            BufferedWriter WriterObj = new BufferedWriter(new FileWriter("output.txt"));

            for (int Output[] : SkyLineOutputs )
            {
               WriterObj.write("("+Output[0]+", "+Output[1]+"), ");
            }

            WriterObj.close();
        }
        catch (IOException e)
        {
            System.err.println("Problem: Writing to the file output.txt.");
        }
    }

    public static class MyCanvas extends JComponent		/* It's our GUI paint class and methods.	*/
    {
        List<int[]> line;
        int h;
        int pix;

        public void setProps(List<int[]> line, int h, int pix)
        {
            this.line = line; this.h = h; this.pix = pix;
            repaint();	// Mark this component to be repainted.
        }

        public void paint(Graphics g)	// It draws the skyline.
        {
            super.paint(g);
            for (int i = 0; i < line.size()-1; ++i)
            {
                g.drawLine(line.get(i)[0]*pix, h-line.get(i)[1]*pix, line.get(i+1)[0]*pix, h-line.get(i+1)[1]*pix);
            }
        }
    }

    public static void PrintAll(List<int[]> SkyLineOutputs)		/* It's our GUI's window size's declarations.	*/
    {
        JFrame window = new JFrame("Skyline");
        MyCanvas canvas = new MyCanvas();
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        if ( MaxScreenWidth <= 150 )
        {
            window.setSize(MaxScreenWidth*20,MaxScreenHeight*20);

            if ( MaxScreenHeight <= 100 )
            {
                canvas.setProps(SkyLineOutputs,MaxScreenHeight*15,12);
            }
            else if ( MaxScreenHeight <= 220 )
            {
                canvas.setProps(SkyLineOutputs,MaxScreenHeight*4,2);
            }
            else if ( MaxScreenHeight <= 500 )
            {
                canvas.setProps(SkyLineOutputs,MaxScreenHeight+100,1);
            }
            else
            {
                canvas.setProps(SkyLineOutputs,MaxScreenHeight-70,1);
            }
        }
        else if ( MaxScreenWidth <= 300 )
        {
            window.setSize(MaxScreenWidth*20,MaxScreenHeight*20);

            if ( MaxScreenHeight <= 100 )
            {
                canvas.setProps(SkyLineOutputs,MaxScreenHeight*15,5);
            }
            else if ( MaxScreenHeight <= 220 )
            {
                canvas.setProps(SkyLineOutputs,MaxScreenHeight*4,2);
            }
            else if ( MaxScreenHeight <= 500 )
            {
                canvas.setProps(SkyLineOutputs,MaxScreenHeight+100,1);
            }
            else
            {
                canvas.setProps(SkyLineOutputs,MaxScreenHeight-70,1);
            }
        }
        else if ( MaxScreenWidth <= 900 )
        {
            window.setSize(MaxScreenWidth*20,MaxScreenHeight*20);

            if ( MaxScreenHeight <= 100 )
            {
                canvas.setProps(SkyLineOutputs,MaxScreenHeight*15,2);
            }
            else if ( MaxScreenHeight <= 220 )
            {
                canvas.setProps(SkyLineOutputs,MaxScreenHeight*4,1);
            }
            else if ( MaxScreenHeight <= 500 )
            {
                canvas.setProps(SkyLineOutputs,MaxScreenHeight+100,1);
            }
            else
            {
                canvas.setProps(SkyLineOutputs,MaxScreenHeight-70,1);
            }
        }
        else
        {
        	window.setSize(MaxScreenWidth*20,MaxScreenHeight*20);

            if ( MaxScreenHeight <= 100 )
            {
                canvas.setProps(SkyLineOutputs,MaxScreenHeight*15,1);
            }
            else if ( MaxScreenHeight <= 220 )
            {
                canvas.setProps(SkyLineOutputs,MaxScreenHeight*4,1);
            }
            else if ( MaxScreenHeight <= 500 )
            {
                canvas.setProps(SkyLineOutputs,MaxScreenHeight+100,1);
            }
            else
            {
                canvas.setProps(SkyLineOutputs,MaxScreenHeight-70,1);
            }
        }
        window.getContentPane().add(canvas);
        window.setVisible(true);
    }

    public static void main(String args[])		// Main function.
    {
        List<int[]> SkyLineInputs = new ArrayList<>();

        SkylineDrawing SkyObj = new SkylineDrawing();

        SkyObj.ReadFile(SkyLineInputs);		// Reading file inputs.

        List<int[]> SkyLineOutputs = SkyObj.CreateSkyline(SkyLineInputs); // Creating skyline.

        SkyObj.WriteToFile(SkyLineOutputs);		// Writing skyline outputs.

        SkyObj.PrintAll(SkyLineOutputs);	// Printing output with GUI.
    }
}
