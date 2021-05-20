
public class CodeGame {
	private static final int EXIT_SUCCESS = 0;

	static {
		try {
			System.loadLibrary("GameLogic");
		}
		catch(UnsatisfiedLinkError e) {
			System.out.println("Failure To Load Library");
		}
	}
	
	public static native int runGame();
	
	public static void main(String[] args) {
		
		if(runGame() == EXIT_SUCCESS) {
			System.out.println("Successful Exit");
		}
		else {
			System.out.println("Error: Unsuccessful Run");
		}
	}
}