package gui.table;

import java.awt.Component;
import java.awt.Container;
import java.util.LinkedList;
import java.util.Vector;

import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.table.DefaultTableModel;
import data_controller.SheetDataController;
import gui.Bounds;
import gui.Strings;

public class TableGuiController {
	
	private JTable table;
	private DefaultTableModel table_model;
	private Container container;
	public void addTable(Container container)
	{
			
		JScrollPane table_with_scroll;
		table_model = new DefaultTableModel(Strings.TABLE_COLUMNS, 0);
		table = new JTable(table_model);
		table.setEnabled(false);
		table_with_scroll = new JScrollPane(table);
		table_with_scroll.setBounds(Bounds.TABLE);
		container.add(table_with_scroll);
		this.container = container;
	}	
	
	public void addRow(String[] row) {
		table_model.addRow(row);
	}	
	
	public void clear() {
		table_model.setRowCount(0);
	}

	public DefaultTableModel getTableModel()
	{
		return table_model;
	}

	public void updateData(String[][] data)
	{
		table_model.setDataVector(data, Strings.TABLE_COLUMNS);
	}
}


class ScrolledTable extends JScrollPane {
	
}
