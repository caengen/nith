import entity.Fruit;
import entity.Salad;

import javax.ejb.Stateless;
import java.util.List;

/**
 * User: Cengen
 * Date: 06/12/13
 * Time: 13:51
 */
@Stateless(name = "CheckoutHandlerEJB")
public class CheckoutHandlerBean {

    public CheckoutHandlerBean() {

    }

    public float calculatePrice(List<Fruit> fruit) {
        float total = 0;

        for (Fruit f : fruit) {
            total += f.getPrice();
        }

        return total;
    }
}
