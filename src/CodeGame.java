/**
 * JNI Number guessing game
 * Java Class executes and calls native c++
 * 
 * @author Zachary Emmons
 * @version 1.8
 * @since 1.0
 */
public class CodeGame {
	//constant for game loop exit
	private static final int EXIT_SUCCESS = 0;

	//attempt to load static dll
	static {
		try {
			System.loadLibrary("GameLogic");
		}
		//error catch for missing library
		catch(UnsatisfiedLinkError e) {
			System.out.println("Failure To Load Library");
		}
	}
	
	/**
	 * Native method calls C++ to run game logic
	 * 
	 * @return int - returns run value on successful or failed game run
	 */
	public static native int runGame();
	
	public static void main(String[] args) {
		
		//check for run success
		if(runGame() == EXIT_SUCCESS) {
			System.out.println("Successful Exit");
		}
		//error return for fatal run error
		else {
			System.out.println("Error: Unsuccessful Run");
		}
	}
}