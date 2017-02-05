import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;


public class OkragSwingPanel extends JPanel implements ActionListener 
{
	Okrag okrag;
	JTextField nazwa, xtext, ytext, rtext;
	
	public OkragSwingPanel(Okrag ok, int xsize, int ysize)
	{
		okrag = ok;
		setSize(xsize, ysize);
		setLayout(new GridLayout(5, 2));
		JLabel nazwa_et = new JLabel("Nazwa: ");
		add(nazwa_et);
		nazwa = new JTextField();
		add(nazwa);
		
		JLabel x_et = new JLabel("X: ");
		add(x_et);
		xtext = new JTextField();
		add(xtext);
		
		JLabel y_et = new JLabel("Y: ");
		add(y_et);
		ytext = new JTextField();
		add(ytext);
		
		JLabel r_et = new JLabel("R: ");
		add(r_et);
		rtext = new JTextField();
		add(rtext);
		
		JButton save = new JButton("Zapisz");
		add(save);
		save.addActionListener(this);
	}
	
	public void actionPerformed(ActionEvent e)
	{
		String s = nazwa.getText();
		double x = Double.parseDouble(xtext.getText());
		double y = Double.parseDouble(ytext.getText());
		double r = Double.parseDouble(rtext.getText());
		
		okrag.setName(s);
		okrag.setx(x);
		okrag.sety(y);
		okrag.setr(r);
		
		System.out.println(okrag.toString());
	}
}
