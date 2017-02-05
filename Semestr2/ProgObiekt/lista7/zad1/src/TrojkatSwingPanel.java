import java.awt.Color;
import java.awt.Container;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;


public class TrojkatSwingPanel extends JPanel implements ActionListener
{
	Trojkat tr;
	JTextField nazwa, punkt_1x, punkt_1y, punkt_2x, punkt_2y, punkt_3x, punkt_3y;
	
	public TrojkatSwingPanel(Trojkat trojkat)
	{
		tr = trojkat;
		setBounds(100, 100, 500, 500);
		setBackground(Color.yellow);
	}
	public TrojkatSwingPanel(Trojkat trojkat, int x, int y)
	{
		tr = trojkat;
		setSize(x, y);
		setLayout(new GridLayout(5, 2));
		JLabel nazwa_etykieta = new JLabel("Nazwa: ");
		add(nazwa_etykieta);
		nazwa = new JTextField(1);
		add(nazwa);
		
		JLabel punkt_1_etykieta = new JLabel("Punkt 1: ");
		add(punkt_1_etykieta);
		Container p1 = new Container();
		p1.setLayout(new GridLayout(1, 2));
		punkt_1x = new JTextField();
		p1.add(punkt_1x);
		punkt_1y = new JTextField();
		p1.add(punkt_1y);
		add(p1);
		
		JLabel punkt_2_etykieta = new JLabel("Punkt 2: ");
		add(punkt_2_etykieta);
		Container p2 = new Container();
		p2.setLayout(new GridLayout(1, 2));
		punkt_2x = new JTextField();
		p2.add(punkt_2x);
		punkt_2y = new JTextField();
		p2.add(punkt_2y);
		add(p2);
		
		JLabel punkt_3_etykieta = new JLabel("Punkt 3: ");
		add(punkt_3_etykieta);
		Container p3 = new Container();
		p3.setLayout(new GridLayout(1, 2));
		punkt_3x = new JTextField();
		p3.add(punkt_3x);
		punkt_3y = new JTextField();
		p3.add(punkt_3y);
		add(p3);
		
		JButton save = new JButton("Zapisz");
		add(save);
		save.addActionListener(this);
	}
	
	public void actionPerformed(ActionEvent e)
	{
		String name = nazwa.getText();
		double x1 = Double.parseDouble(punkt_1x.getText());
		double y1 = Double.parseDouble(punkt_1y.getText());
		double x2 = Double.parseDouble(punkt_2x.getText());
		double y2 = Double.parseDouble(punkt_2y.getText());
		double x3 = Double.parseDouble(punkt_3x.getText());
		double y3 = Double.parseDouble(punkt_3y.getText());
		
		tr.update(name, x1, y1, x2, y2, x3, y3);
		System.out.println(tr.toString());
	}
}
