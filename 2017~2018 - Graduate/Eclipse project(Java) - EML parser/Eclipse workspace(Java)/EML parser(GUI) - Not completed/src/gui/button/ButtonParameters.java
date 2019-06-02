package gui.button;

import java.awt.Rectangle;

import gui.Bounds;
import gui.Strings;
import gui.Bounds.Button;
import gui.Bounds.SpecifyRange;


final class ButtonParameters {
	
	public abstract static class Data {
		 Rectangle bounds;
		 boolean enabled;
	}
	
	
	public static class MultiLine extends Data{
		String strings[];
	}
	public static class SingleLine extends Data{
		String string;
	}

	private static final class LoadEmls extends MultiLine {
		LoadEmls() {
			strings = Strings.LOAD_EMLS;
			bounds = Bounds.Button.LOAD_EMLS;
			enabled = true;
		}
	}

	private static final class LoadSheet extends MultiLine {
		LoadSheet() {
			strings = Strings.LOAD_SHEET;
			bounds = Bounds.Button.LOAD_SHEET;
			enabled = true;
		}
	}

	private static final class Save extends SingleLine {
		Save() {
			string = Strings.SAVE;
			bounds = Bounds.Button.SAVE;
			enabled = false;
		}
	}

	private static final class SaveAs extends SingleLine {
		SaveAs() {
			string = Strings.SAVE_AS;
			bounds = Bounds.Button.SAVE_AS;
			enabled = false;
		}
	}

	private static final class Clear extends SingleLine {
		Clear() {
			string = Strings.CLEAR;
			bounds = Bounds.Button.CLEAR;
			enabled = false;
		}
	}
	

	public static final MultiLine LOAD_EMLS, LOAD_SHEET;
	public static final SingleLine SAVE, SAVE_AS, CLEAR;


	static {
		LOAD_EMLS = new LoadEmls();
		LOAD_SHEET = new LoadSheet();
		SAVE = new Save();
		SAVE_AS = new SaveAs();
		CLEAR = new Clear();
	}
}