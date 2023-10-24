package traccia;

public class Transaction {
  private double amount=0;
  private boolean isExpense=false;
  private String category;
  private long dateTime;

  // setter

  public Transaction setAmount(double aAmount){
    amount = aAmount;
    return this;
  }

  public Transaction setIsExpense(boolean aIsExpense){
    isExpense = aIsExpense;
    return this;
  }
  
  public Transaction setCategory(String aCategory){
    category = aCategory;
    return this;
  }

  public Transaction setDateTime(long aDateTime){
    dateTime = aDateTime;
    return this;
  }

  public Transaction build(){
    return this;
  }

  // getter
  
  public double getAmount(){
    return amount;
  }

  public boolean getIsExpense(){
    return isExpense;
  }

  public String getCategory(){
    return category;
  }

  public long getDateTime(){
    return dateTime;
  }
}
