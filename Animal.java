class Animal
{
 public double height;
 private String name;
 public double speed;
 private double weight;
 private String sound;
 
 public void setName(String n){ name = n;}
 public void setheight(int h){ height = h;}
 public void setSound(String s){ sound = s;}
 public void setSpeed(double sp){ speed = sp*10;}
 public void setWeight(int newWeight){
	        if (newWeight > 0){
	            weight = newWeight;
	        } else {
	            System.out.println("Weight must be bigger than 0");
	        }
	    }
public double getWeight(){ return weight; }

 public String getName(){ return name;}
 public double getheight( ){ return height;}
 public String getSound(){ return sound;}
 public double getSpeed(){ return speed;}
 private void bePrivate(){ System.out.println("I'm a private method Animal"); }

 public static void main(String[] args){

	         
  Animal dog = new Animal();
  dog.setName("Grover");
  System.out.println(dog.getName());
	         
}
}

 
