package gui.range_specifying.radioButton;

import java.awt.Rectangle;

import gui.Bounds;
import gui.Strings;

class RadioButtonParameters {
		static class Data {
			String string;
			Rectangle bounds;
			boolean checked;
		}
		static class All extends Data{
			All() {
				string = Strings.ALL;
				bounds = Bounds.SpecifyRange.ALL;
				checked = true;
			}
		}
		static class Range extends Data{
			Range() {
				string = Strings.RANGE;
				bounds = Bounds.SpecifyRange.RANGE;
				checked = false;
			}
		}
		static final Data ALL, RANGE;
		static {
			ALL = new All();
			RANGE = new Range();
		}
	}