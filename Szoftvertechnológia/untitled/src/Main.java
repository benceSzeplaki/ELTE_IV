public class Main {

    private static boolean isItHorizontal(int iIndex, int jIndex, int[][] field) {
        boolean isItHorizontal = false;

        if(jIndex != field[iIndex].length - 1) {
            if(field[iIndex][jIndex + 1] == 1){
                isItHorizontal = true;
            }
        }

        return isItHorizontal;
    }

    private static boolean isItVertical(int iIndex, int jIndex, int[][] field) {
        boolean isItVertical = false;

        if(iIndex != field.length - 1) {
            if(field[iIndex + 1][jIndex] == 1){
                isItVertical = true;
            }
        }

        return isItVertical;
    }

    public static boolean fieldValidator(int[][] field) {
        boolean isValid = true;
        int countBattleship = 0;    // 1
        int countCruisers = 0;      // 2
        int countDestroyers = 0;    // 3
        int countSubmarines = 0;    // 4

        int howLongIsTheShip;

        for (int i = 0; i < field.length; i++) {
            for (int j = 0; j < field[i].length; j++) {
                if(isValid) {
                    if(field[i][j] == 1) {
                        if(i == 0) {
                            if(j == 0) {
                                if(isItHorizontal(i, j, field)) {
                                    howLongIsTheShip = howLongIsTheHorizontalShip(i, j, field);
                                    storeShipLength(howLongIsTheShip, countBattleship, countCruisers, countDestroyers, countSubmarines, isValid);
                                } else if(isItVertical(i, j, field)) {
                                    howLongIsTheShip = howLongIsVerticalShip(i, j, field);
                                    storeShipLength(howLongIsTheShip, countBattleship, countCruisers, countDestroyers, countSubmarines, isValid);
                                } else {
                                    if(isSurroundingFree(i, j, field)){
                                        countSubmarines++;
                                    }
                                }
                            } else if(j == field.length-1) {

                            } else {

                            }
                        } else if(i == field.length-1) {
                            if(j == 0){

                            } else if(j == field.length-1) {

                            } else {

                            }
                        } else {
                            if(j == 0){

                            } else if(j == field.length-1) {

                            } else {

                            }
                        }
                    }
                } else {
                    return false;
                }
            }
        }
        return true;
    }

    private static void storeShipLength(int howLongIsTheShip, int countBattleship, int countCruisers, int countDestroyers, int countSubmarines, boolean isValid) {
        switch (howLongIsTheShip) {
            case 1 -> {
                countSubmarines++;
                if (countSubmarines > 4) {
                    isValid = false;
                }
            }
            case 2 -> {
                countDestroyers++;
                if (countDestroyers > 3) {
                    isValid = false;
                }
            }
            case 3 -> {
                countCruisers++;
                if (countCruisers > 2) {
                    isValid = false;
                }
            }
            case 4 -> {
                countBattleship++;
                if (countBattleship > 1) {
                    isValid = false;
                }
            }
            default -> {
                isValid = false;
            }
        }
    }

    private static int howLongIsTheHorizontalShip(int iIndex, int jIndex, int[][] field) {
        int count = 0;
        int j = jIndex;
        if( jIndex == field[iIndex].length - 1){
            count++;
            return count;
        } else if(jIndex == field[iIndex].length - 2){
            while(j < jIndex + 2) {
                if(field[iIndex][j] == 1){
                    count++;
                }
                j++;
            }
        } else if(jIndex == field[iIndex].length - 3){
            while(j < jIndex + 3) {
                if(field[iIndex][j] == 1){
                    count++;
                }
                j++;
            }
        } else {
            while (j < jIndex + 4) {
                if (field[iIndex][j] == 1) {
                    count++;
                }
                j++;
            }
        }
        return count;
    }

    private static int howLongIsVerticalShip(int iIndex, int jIndex, int[][] field) {
        int count = 0;
        int i = iIndex;
        if( iIndex == field.length - 1){
            count++;
            return count;
        } else if(iIndex == field.length - 2){
            while(i < iIndex + 2) {
                if(field[i][jIndex] == 1){
                    count++;
                }
                i++;
            }
        } else if(iIndex == field.length - 3){
            while(i < iIndex + 3) {
                if(field[i][jIndex] == 1){
                    count++;
                }
                i++;
            }
        } else {
            while(i < iIndex + 4) {
                if(field[i][jIndex] == 1){
                    count++;
                }
                i++;
            }
        }
        return count;
    }

    private static boolean isSurroundingFree(int i, int j, int[][] field) {
        boolean isSurroundingFree = false;

        if(i == 0){
            if(j == 0){
                if(field[i+1][j] == 0 && field[i][j+1] == 0 && field[i+1][j+1] == 0){
                    isSurroundingFree = true;
                }
            } else if(j == field[i].length - 1) {
                if(field[i][j-1] == 0 && field[i+1][j] == 0 && field[i+1][j-1] == 0){
                    isSurroundingFree = true;
                }
            } else {
                if(field[i+1][j] == 0 && field[i+1][j-1] == 0 && field[i+1][j+1] == 0 && field[i][j-1] == 0 && field[i][j+1] == 0){
                    isSurroundingFree = true;
                }
            }
        } else if(i == field.length - 1){
            if(j == 0){
                if(field[i-1][j] == 0 && field[i][j+1] == 0 && field[i-1][j+1] == 0){
                    isSurroundingFree = true;
                }
            } else if(j == field[i].length - 1) {
                if(field[i-1][j] == 0 && field[i][j-1] == 0 && field[i-1][j-1] == 0){
                    isSurroundingFree = true;
                }
            } else {
                if(field[i][j-1] == 0 && field[i-1][j-1] == 0 && field[i-1][j] == 0 && field[i-1][j+1] == 0 && field[i][j+1] == 0){
                    isSurroundingFree = true;
                }
            }
        } else {
            if(j == 0) {
                if(field[i-1][j] == 0 && field[i-1][j+1] == 0 && field[i][j+1] == 0 && field[i+1][j+1] == 0 && field[i+1][j] == 0){
                    isSurroundingFree = true;
                }
            } else if(j == field[i].length - 1) {
                if(field[i-1][j] == 0 && field[i-1][j-1] == 0 && field[i][j-1] == 0 && field[i+1][j-1] == 0 && field[i+1][j] == 0){
                    isSurroundingFree = true;
                }
            } else {
                if(field[i-1][j] == 0 && field[i+1][j] == 0 && field[i][j-1] == 0 && field[i][j+1] == 0 && field[i-1][j-1] == 0 && field[i-1][j+1] == 0 && field[i+1][j-1] == 0 && field[i+1][j+1] == 0) {
                    isSurroundingFree = true;
                }
            }
        }

        return isSurroundingFree;
    }

    public static void main(String[] args) {
        int[][] battleField = { {1, 0, 0, 0, 0, 1, 1, 0, 0, 0},
                                {1, 0, 1, 0, 0, 0, 0, 0, 1, 0},
                                {1, 0, 1, 0, 1, 1, 1, 0, 1, 0},
                                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
                                {0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
                                {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
        if(fieldValidator(battleField)){
            System.out.println("This is a valid field.");
        } else {
            System.out.println("This is not a valid field.");
        }
    }
}
