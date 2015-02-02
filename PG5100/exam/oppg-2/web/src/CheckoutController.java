import com.sun.faces.mgbean.ManagedBeanInfo;
import entity.Fruit;
import entity.Salad;

import javax.annotation.PostConstruct;
import javax.ejb.EJB;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.ManagedProperty;
import javax.faces.bean.SessionScoped;
import java.util.List;

/**
 * User: Cengen
 * Date: 06/12/13
 * Time: 14:21
 */
@ManagedBean
@SessionScoped
public class CheckoutController {
    private List<Fruit> checkedFruit;
    private float total;

    @ManagedProperty(value="#{fruitManagerController}")
    private FruitManagerController fruitManagerController;

    @EJB
    CheckoutHandlerBean checkoutHandlerBean;

    public CheckoutController() {

    }

    //Gets 
    @PostConstruct
    public void setupCheckout() {
        checkedFruit = fruitManagerController.getCheckedFruits();

        total = checkoutHandlerBean.calculatePrice(checkedFruit);
    }

    public String goBack() {
        fruitManagerController.clearChecked();
        return "saladmanager?faces-redirect=true";
    }

    public float getTotal() {
        return total;
    }

    public void setTotal(float total) {
        this.total = total;
    }

    public List<Fruit> getCheckedFruit() {
        return checkedFruit;
    }

    public void setCheckedFruit(List<Fruit> checkedFruit) {
        this.checkedFruit = checkedFruit;
    }

    public void setFruitManagerController(FruitManagerController fruitManagerController) {
        this.fruitManagerController = fruitManagerController;
    }
}
