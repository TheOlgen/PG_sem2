package projekt.program;
import projekt.program.Organisms.Animal;
import projekt.program.Organisms.Animals.*;
import projekt.program.Organisms.Plant;
import projekt.program.Organisms.Plants.Barszcz;
import projekt.program.Organisms.Plants.Dandelion;
import projekt.program.Organisms.Plants.DeadlyNightshade;
import projekt.program.Organisms.Plants.Guarana;

import javax.swing.*;
import java.awt.*;

public class Panel extends JPanel {
    private int RECT_SIZE;
    int width, height;
    World swiat;
    public Panel(int height, int width, int RECT_SIZE, World swiat){
        setPreferredSize(new Dimension(width*RECT_SIZE+1, (10+height)*RECT_SIZE+10));
        this.width = width;
        this.height = height;
        this.swiat = swiat;
        this.RECT_SIZE = RECT_SIZE;
    }
    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        Graphics2D g2d = (Graphics2D) g;

        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                //g2d.drawRect(j*RECT_SIZE, i*RECT_SIZE, RECT_SIZE, RECT_SIZE);
                // Get the organism at the current position
                Organism organism = swiat.getOrganismAtPosition(j, i);
                if(organism instanceof Animal){
                    g2d.setColor(getColorForOrganism(organism));
                    g2d.fillOval(j*RECT_SIZE, i*RECT_SIZE, RECT_SIZE, RECT_SIZE);
                    g2d.setColor(Color.BLACK);
                    g2d.drawOval(j*RECT_SIZE, i*RECT_SIZE, RECT_SIZE, RECT_SIZE);
                }
                if(organism instanceof Plant) {
                    g2d.setColor(Color.GREEN);
                    g2d.fillRect(j * RECT_SIZE, i * RECT_SIZE, RECT_SIZE, RECT_SIZE);
                    g2d.setColor(getColorForOrganism(organism));
                    for (int k = 0; k < 4; k++) {
                        int dotX = j * RECT_SIZE + RECT_SIZE / 4 + (k % 2) * RECT_SIZE / 2 - RECT_SIZE / 8;
                        int dotY = i * RECT_SIZE + RECT_SIZE / 4 + (k / 2) * RECT_SIZE / 2 - RECT_SIZE / 8;
                        if(organism instanceof DeadlyNightshade || organism instanceof Guarana || organism instanceof Barszcz){
                            g2d.fillOval(dotX, dotY, RECT_SIZE / 6, RECT_SIZE / 6);
                        }
                        if(organism instanceof Dandelion){
                            g2d.drawLine(dotX,dotY,dotX+ RECT_SIZE / 6, dotY+RECT_SIZE / 6);
                            g2d.drawLine(dotX+ RECT_SIZE / 6,dotY,dotX, dotY+RECT_SIZE / 6);
                            g2d.drawLine(dotX+ RECT_SIZE / 12, dotY, dotX+RECT_SIZE / 12, dotY+RECT_SIZE / 6);
                            g2d.drawLine(dotX, dotY+ RECT_SIZE / 12, dotX+RECT_SIZE / 6, dotY+RECT_SIZE / 12);
                        }
                    }
                    g2d.setColor(Color.BLACK);
                }
            }
        }
        g2d.drawRect(0, 0, RECT_SIZE*width, RECT_SIZE*height);
        g2d.drawRect(0,RECT_SIZE*(width+1), RECT_SIZE*width, RECT_SIZE*3);
        String message = "Aktualna tura: " +swiat.getTurn();
        g2d.drawString(message, RECT_SIZE,RECT_SIZE*(width+2));
        //g2d.drawString(swiat.getMessage(), RECT_SIZE,RECT_SIZE*(width+2)+10);
    }
    // Method to get the color for each type of organism
    private Color getColorForOrganism(Organism organism) {
        //animals
        if (organism instanceof Wolf) {
            return Color.GRAY;
        } else if (organism instanceof Sheep) {
            return Color.WHITE;
        } else if (organism instanceof Turtle) {
            return Color.green.darker().darker();
        } else if (organism instanceof Fox) {
            return Color.ORANGE;
        } else if (organism instanceof Antelope) {
            return Color.YELLOW;
        } else if (organism instanceof Human) {
            return Color.PINK;
        }
        //plants
        else if (organism instanceof Guarana) {
            return Color.red;
        } else if (organism instanceof Dandelion) {
            return Color.yellow;
        } else if (organism instanceof DeadlyNightshade) {
            return Color.MAGENTA;
        } else if (organism instanceof Barszcz) {
            return Color.white;
        }

        // Default color if the organism type is unknown
        return Color.BLACK;
    }
}
