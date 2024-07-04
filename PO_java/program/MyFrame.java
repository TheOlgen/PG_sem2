package projekt.program;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class MyFrame extends JFrame implements ActionListener {
    private static final int RECT_SIZE = 30;
    private static final int LOCATION = 40;
    private JButton supermoc, up, down, left, right, save;
    private Panel panel;
    World swiat;
    public MyFrame(int height, int width, World swiat) {
        super("Olga Rodziewicz s198421 gr4");
        this.swiat = swiat;
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize((width + 5) * RECT_SIZE, (height + 8) * RECT_SIZE);
        setLocation(LOCATION, LOCATION);

        setLayout(new FlowLayout(FlowLayout.CENTER)); //layout pomagalacy w estetycznym wyglądzie
        left = new JButton("Go left");
        left.addActionListener(this);
        add(left);
        up = new JButton("Go up");
        up.addActionListener(this);
        add(up);
        down = new JButton("Go down");
        down.addActionListener(this);
        add(down);
        right = new JButton("Go right");
        right.addActionListener(this);
        add(right);
        supermoc = new JButton("Use superpower");
        supermoc.addActionListener(this);
        add(supermoc);
        save = new JButton("Save simulation");
        save.addActionListener(this);
        add(save);

        panel = new Panel(height, width, RECT_SIZE, swiat);
        add(panel);

        setVisible(true);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        Object source = e.getSource();
        // commands "WSAD" for moving human, "z" for saving the simulation
        if (source == up){
            newTurn('w');
        }
        if (source == down){
            newTurn('s');
        }
        if (source == left){
            newTurn('a');
        }
        if (source == right){
            newTurn('d');
        }
        if (source == supermoc) {
            newTurn('n');
        }
        if (source == save) {
            newTurn('z');
        }
    }
    private void newTurn(char command){
        swiat.executeTurn(command);
        panel.repaint();
    }
}
