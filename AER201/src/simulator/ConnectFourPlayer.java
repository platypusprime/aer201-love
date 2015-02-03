package simulator;

public interface ConnectFourPlayer {

	// public PlayerState getState();
	//
	// public int moveToHopper();
	//
	// public int moveToCornerHopper();
	//
	// public void moveToBoard();
	//
	public int getMove();

	public long getPeriod();

}

enum PlayerState {
	MOVING, WORKING, AT_CORNER, AT_CENTER, AT_BOARD, AT_START;
}
