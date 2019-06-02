package ui.gui_controller.table;
import java.awt.Container;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.table.DefaultTableModel;

import ui.Bounds;
import ui.Strings;


public class TableGUI_Controller
{	
	public void addTableTo(Container container)
	{		
		JTable table;
		DefaultTableModel table_model;		
		JScrollPane table_with_scroll;		
		
		table_model = new DefaultTableModel(Strings.TABLE_COLUMNS, 0);
		table = new JTable(table_model);
		table_with_scroll = new JScrollPane(table);
		table_with_scroll.setBounds(Bounds.TABLE);
		container.add(table_with_scroll);
	}
}


