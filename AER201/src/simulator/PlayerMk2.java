package simulator;

public class PlayerMk2 implements ConnectFourPlayer {

	private final C4Game game;
	private final BoardCell color;
	private final long speed;

	private static final int[] PREFERRED_COLUMNS = { 3, 2, 4, 1, 5, 0, 6 };

	public PlayerMk2(C4Game game, BoardCell color, long speed) {
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
				int[] sets = C4Board.countSets(boardState, col, row, color);
				score = sets[0] + sets[1] * 10 + sets[2] * 100 + sets[3] * 1000;
			}
			if (score > highestGainScore) {
				highestGainCol = col;
				highestGainScore = score;
			}
		}

		// only block opponents when they have a chance to get connect fours
		for (int col = 0; col < C4Board.MAX_COLUMN; col++) {
			int row = getAvailableRow(boardState, col);
			int score = 0;
			if (row != -1) {
				score = 1000 * C4Board.countSets(boardState, col, row,
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
