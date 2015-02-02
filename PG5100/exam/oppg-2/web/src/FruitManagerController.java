import entity.Fruit;
import entity.Salad;

import javax.annotation.PostConstruct;
import javax.ejb.EJB;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.SessionScoped;
import java.util.*;

/**
 * User: Cengen
 * Date: 06/12/13
 * Time: 00:32
 */
@ManagedBean
@SessionScoped
public class FruitManagerController {
    private List<Salad> oldSalads;
    private List<Fruit> fruitList;
    private Map<Fruit, Boolean> checked;

    @EJB
    private FruitHandlerBean fruitHandlerBean;
    @EJB
    UserHandlerBean userHandlerBean;

    public FruitManagerController() {
        checked = new HashMap<Fruit, Boolean>();
    }

    @PostConstruct
    public void fruitManagerSetup() {
        getFruitVariants();
        getSaladHistory();
    }

    public void getFruitVariants() {
        setFruitList(fruitHandlerBean.getAllFruitVariants());
    }

    public void getSaladHistory() {
        setOldSalads(fruitHandlerBean.getUserSalads());
    }

    public List<Fruit> getCheckedFruits() {
        List<Fruit> checkedFruits = new ArrayList<Fruit>();

        if (Collections.frequency(checked.values(), Boolean.TRUE) >= 4) {
            Iterator itr = checked.entrySet().iterator();
            while(itr.hasNext()) {
                Map.Entry pairs = (Map.Entry)itr.next();
                if ((Boolean)pairs.getValue()) {
                    checkedFruits.add((Fruit) pairs.getKey());
                }
            }

            return checkedFruits;
        }

        else {
            return null;
        }
    }

    public String submitFruitSalad() {
        List<Fruit> checkedFruit = getCheckedFruits();
        if (checkedFruit != null) {
            Salad salad = new Salad();

            salad.setFruits(checkedFruit);
            userHandlerBean.updateUser(salad);

            return "checkout?faces-redirect=true";
        }

        return "saladmanager?faces-redirect=true";
    }

    public void clearChecked() {
        getChecked().clear();
    }

    public List<Fruit> getFruitList() {
        return fruitList;
    }

    public void setFruitList(List<Fruit> fruitList) {
        this.fruitList = fruitList;
    }

    public Map<Fruit, Boolean> getChecked() {
        return checked;
    }

    public void setChecked(Map<Fruit, Boolean> checked) {
        this.checked = checked;
    }

    public List<Salad> getOldSalads() {
        return oldSalads;
    }

    public void setOldSalads(List<Salad> oldSalads) {
        this.oldSalads = oldSalads;
    }
}
