import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class Main 
{
	public static void main(String[] args) 
	{
		JFrame frametr = new JFrame();
		frametr.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		Trojkat trojkat = new Trojkat(1.0,2.0,3.0,4.0,5.0,6.0,"asdf");
		TrojkatSwingPanel paneltr = new TrojkatSwingPanel(trojkat,500,500);
		frametr.getContentPane().add(paneltr);
		frametr.pack();
		
		
		JFrame frameok = new JFrame();
		frameok.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		Okrag okrag = new Okrag(1.0,2.0,3.0,"asdf");
		OkragSwingPanel panelok = new OkragSwingPanel(okrag,500,500);
		frameok.getContentPane().add(panelok);
		frameok.pack();
		
		
		frameok.setVisible(true);
		frametr.setVisible(true);
	}

}
