package simulator;

public class PlayerMk1 implements ConnectFourPlayer {

	private final C4Game game;
	private final BoardCell color;
	private final long speed;

	private static final int[] PREFERRED_COLUMNS = { 3, 2, 4, 1, 5, 0, 6 };

	public PlayerMk1(C4Game game, BoardCell color, long speed) {
		this.game = game;
		this.color = color;
		this.speed = speed;
	}

	@Override
	public int getMove() {
		BoardCell[][] boardState = game.getBoardState();

		int highestGainCol = 0, highestGainScore = 0;
		int highestLossCol = 0, highestLossScore = 0;

		// find possible chains
		for (int col : PREFERRED_COLUMNS) {
			int row = getAvailableRow(boardState, col);
			int score = 0;
			if (row != -1) {
				score = 1 + 6 * C4Board.countSets(boardState, col, row, color)[3];
			}
			if (score > highestGainScore) {
				highestGainCol = col;
				highestGainScore = score;
			}
		}

		// check opponent chains
		for (int col = 0; col < C4Board.MAX_COLUMN; col++) {
			int row = getAvailableRow(boardState, col);
			int score = 0;
			if (row != -1) {
				score = 1 + 6 * C4Board.countSets(boardState, col, row,
						color.opposite())[3];
			}
			if (score > highestLossScore) {
				highestLossCol = col;
				highestLossScore = score;
			}
		}

		return highestLossScore > highestGainScore ? highestLossCol
				: highestGainCol;
	}

	@Override
	public long getPeriod() {
		return speed;
	}

	private int getAvailableRow(BoardCell[][] boardState, int col) {

		for (int row = 0; row < C4Board.MAX_ROW; row++)
			if (boardState[col][row] == BoardCell.EMPTY)
				return row;

		return -1;
	}

}
