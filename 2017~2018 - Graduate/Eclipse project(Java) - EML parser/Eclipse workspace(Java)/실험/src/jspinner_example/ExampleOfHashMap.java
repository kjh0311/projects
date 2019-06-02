package jspinner_example;

import java.util.HashMap;

enum Keys {
	a,b,c;
}

public class ExampleOfHashMap
{
	public static void main(String args[]) {
		new ExampleOfHashMap();
	}
	ExampleOfHashMap(){
		HashMap<Keys,Object> map = new HashMap<Keys, Object>();
		
		map.put(Keys.a, 1);
		map.put(Keys.b, 2);
		map.put(Keys.c, 3);
		
		System.out.println(map.get(Keys.b));
        
	}
}
